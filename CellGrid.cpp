#include "CellGrid.h"

#include "BaseCell.h"

#include "BaseAcceptNewConfigRule.h"
#include "BaseEntireGridRule.h"
#include "BaseSingleCellRule.h"

#include "ofMain.h"

#include "MegastructureConstants.h"

CellGrid::CellGrid(void)
{
	gridWidth = 0;
	gridHeight = 0;
	cellGeneration = 0;
	total_decay = 0;

	_currentCells = NULL;
	_nextCells = NULL;
	_edges = NULL;
}

CellGrid::~CellGrid(void)
{
}

void CellGrid::AddCellRule(BaseSingleCellRule* newRule)
{
	BaseSingleCellRule* rule = newRule->Copy();
	_singleCellRules.push_back(rule);
}

void CellGrid::AddGlobalRule(BaseEntireGridRule* newRule)
{
	BaseEntireGridRule* rule = newRule->Copy();
	_entireGridRules.push_back(rule);
}

void CellGrid::AddAcceptRule(BaseAcceptNewConfigRule* newRule)
{
	BaseAcceptNewConfigRule* rule = newRule->Copy();
	_acceptNewConfigRules.push_back(rule);
}

const BaseCell* CellGrid::GetCurrentConfigurationEffectiveAt(int x, int y)
{
	return getEffectiveCell(_currentCells, x, y);
}

const BaseCell* CellGrid::GetNextConfigurationEffectiveAt(int x, int y)
{
	return getEffectiveCell(_nextCells, x, y);
}

const BaseCell* CellGrid::GetCurrentConfigurationAt(int x, int y)
{
	return getCell(_currentCells, x, y);
}

const BaseCell* CellGrid::GetNextConfigurationAt(int x, int y)
{
	return getCell(_nextCells, x, y);
}

BaseCell* CellGrid::GetNextConfigurationForEditAt(int x, int y)
{
	return getCellForEdit(_nextCells, x, y);
}

const BaseCell* CellGrid::getCell(BaseCell*** target, int x, int y)
{
	int useX = (x + gridWidth) % gridWidth;
	int useY = (y + gridHeight) % gridHeight;

	return static_cast<const BaseCell*>(target[useX][useY]);
}

const BaseCell* CellGrid::getEffectiveCell(BaseCell*** target, int x, int y)
{
	//here we go again, on our own :/

	/*
	DIAGRAM -- start on top left, go right

	******+
	x	  +		-
	x	  +
	x	  +		5 = gridHeight
	x	  +
	x	  +		-
	x------
	 | 5 |

	*/

	int topLeft_corner = 0;
	int topRight_corner = topLeft_corner + gridWidth + 1;
	int bottomRight_corner = topRight_corner + gridHeight + 1;
	int bottomLeft_corner = bottomRight_corner + gridWidth + 1;


	if(x == -1 && y == -1)
	{
		return _edges[topLeft_corner];
	}

	if(x == gridWidth && y == 0)
	{
		return _edges[topRight_corner];
	}

	if(x == gridWidth && y == gridHeight)
	{
		return _edges[bottomRight_corner];
	}

	if(x == -1 && y == gridHeight)
	{
		return _edges[bottomLeft_corner];
	}

	//edges ....
	if(y == -1)
	{
		return _edges[topLeft_corner + x + 1];
	}

	if(x == gridWidth)
	{
		return _edges[topRight_corner + y + 1];
	}

	if(y == gridHeight)
	{
		return _edges[bottomRight_corner + 1 + (gridWidth - x - 1)];
	}

	if(x == -1) //final case
	{
		return _edges[bottomLeft_corner + 1 + (gridHeight - y - 1)];
	}

	///still here????? I guess you want SOMETHING FROM THE ACTUAL GRID
	return target[x][y];
}

BaseCell* CellGrid::getCellForEdit(BaseCell*** target, int x, int y)
{
	int useX = (x + gridWidth) % gridWidth;
	int useY = (y + gridHeight) % gridHeight;

	return target[useX][useY];
}


void CellGrid::InitCells(CellTypes cellTypeToCreate, BaseCell**** targetGrid)
{
	//create new grid of cells
	(*targetGrid) = new BaseCell**[gridWidth];
	for(int x = 0; x < gridWidth; x++)
	{
		(*targetGrid)[x] = new BaseCell*[gridHeight];
		for(int y = 0; y < gridHeight; y++)
		{
			(*targetGrid)[x][y] = CellFactory::CreateBaseCell(cellTypeToCreate);
		}
	}
}

void CellGrid::Setup(CellTypes cellTypeToCreate, int width, int height)
{
	gridWidth = width;
	gridHeight = height;
	InitCells(cellTypeToCreate, &_currentCells);
	InitCells(cellTypeToCreate, &_nextCells);

	int totalEdges = (width + 1)*2 + (height + 1) *2;
	_edges = new BaseCell*[totalEdges];
	for(int i = 0; i < totalEdges; i++)
	{
		_edges[i] = CellFactory::CreateBaseCell(cellTypeToCreate);
	}

}

void CellGrid::Update(int speed)
{
	//decide if another generation is necessary (else exit)
	int frames = ofGetFrameNum();
	float framerate = ofGetFrameRate();
	int modFrames = max(1, (int)(framerate / speed));
	if(frames % modFrames != 0)
	{
		return;
	}

	//another generation
	cellGeneration ++;

	int tries = 1;

	bool accepted = false;
	while(!accepted && tries < 100)
	{
		copyToNext();
		applySingleCellRules();
		applyEntireGridRules();
		accepted = doesAcceptNewConfiguration();
		tries++;
	}

	if(!accepted)
	{
		//ya kaduda -- we can't sir
		int j = 4;
		exit(100);
	}

	//we should be accepted by now, so copy back to _currentGrid
	copyToTarget(_nextCells, _currentCells);

	//update current decay counts
	total_decay = 0;
	for(int x = 0; x < gridWidth; x++)
	{
		for(int y = 0; y < gridHeight; y++)
		{
			total_decay += _currentCells[x][y]->CellProperties.at("decay");
		}
	}
}

void CellGrid::copyToTarget(BaseCell *** source, BaseCell *** target)
{
	for(int x = 0; x < gridWidth; x++)
	{
		for(int y = 0; y < gridHeight; y++)
		{
			delete target[x][y];
			target[x][y] = source[x][y]->Copy();
		}
	}
}

void CellGrid::applySingleCellRules()
{
	//apply rules for this generation
	for(int x = 0; x < gridWidth; x++)
	{
		for(int y = 0; y < gridHeight; y++)
		{
			for(int i = 0; i < _singleCellRules.size(); i++)
			{
				_singleCellRules[i]->ApplyRule(_nextCells[x][y], this, x, y);
			}
		}
	}
}

void CellGrid::applyEntireGridRules()
{
	for(unsigned int i = 0; i < _entireGridRules.size(); i++)
	{
		_entireGridRules[i]->ApplyRule(this);
	}
}

bool CellGrid::doesAcceptNewConfiguration()
{
	for(unsigned int i = 0; i < _acceptNewConfigRules.size(); i++)
	{
		if(!_acceptNewConfigRules[i]->AcceptRule(this))
			return false;
	}

	//made it through them all ... rejoice
	return true;
}

void CellGrid::copyToNext()
{
	//copy next generation into current generation
	copyToTarget(_currentCells, _nextCells);
}

void CellGrid::Draw(int screenwid, int screenhei)
{
	//run over current generation and draw them
	float cellWidth = screenwid / ((float) gridWidth + 2);
	float cellHeight = screenhei / ((float) gridHeight + 2);

	for(int x = -1; x < gridWidth+1; x++)
	{
		for(int y = -1; y < gridHeight+1; y++)
		{
			float coordx = (x + 1.5) * cellWidth;
			float coordy = (y + 1.5) * cellHeight;

			int decay, generation, group;
			int rel_decay = 255 / MAX_DECAY;
			int rel_generation = 255 / MAX_GENERATIONS;
			decay = GetCurrentConfigurationEffectiveAt(x, y)->CellProperties.at("decay");
			generation = GetCurrentConfigurationEffectiveAt(x, y)->CellProperties.at("generation");
			group = GetCurrentConfigurationEffectiveAt(x, y)->CellProperties.at("group");

			ofSetRectMode(OF_RECTMODE_CENTER);
			ofFill();

			//Border -- gets lighter as decays
			if(group == 1)
			{
				ofSetColor(0, 0, 255, (MAX_DECAY - decay) * rel_decay);
			}
			else
			{
				ofSetColor(0, 255, 0, (MAX_DECAY - decay) * rel_decay);
			}
			ofRect(coordx, coordy, 0, cellWidth, cellHeight);

			//white "background" square"
			ofSetColor(255);
			ofRect(coordx, coordy, 0, cellWidth * 0.8, cellHeight * 0.9);

			//if(decay < MAX_CONNECTED_DECAY)
			//{
			//	//draw double border
			//	ofSetColor(decay * rel_decay);
			//	ofRect(coordx, coordy, 0, cellWidth * 0.7, cellHeight * 0.7);

			//	//white "background" square
			//	ofSetColor(255);
			//	ofRect(coordx, coordy, 0, cellWidth * 0.6, cellHeight * 0.6);
			//}

			//inner square -- generation indicator (redder is newer)
			ofSetColor(255, 255 - rel_generation * generation, 255 - rel_generation * generation);
			ofRect(coordx, coordy, 0, cellWidth * 0.2, cellHeight * 0.2);
		}
	}

	//draw generation count
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(0,0,255, 150);
	ofRect(screenwid - 200, screenhei - 30, 200, 30);
	ofSetColor(255);
	string genStr = "cellular generation " + ofToString(cellGeneration) + "\r\n"
		+ "Total/avg decay " + ofToString(total_decay) + "/" + ofToString(total_decay / ((float) gridWidth * gridHeight), 2) ;
	ofDrawBitmapString(genStr, screenwid - 200, screenhei - 15);
}