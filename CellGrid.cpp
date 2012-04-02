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

const BaseCell* CellGrid::GetCurrentConfigurationAt(int x, int y)
{
	return getCell(_currentCells, x, y);
}

const BaseCell* CellGrid::GetNextConfiguratonAt(int x, int y)
{
	return getCell(_nextCells, x, y);
}

const BaseCell* CellGrid::getCell(BaseCell*** target, int x, int y)
{
	int useX = (x + gridWidth) % gridWidth;
	int useY = (y + gridHeight) % gridHeight;

	return static_cast<const BaseCell*>(target[useX][useY]);
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
}

void CellGrid::Update(int speed)
{
	//decide if another generation is necessary (else exit)
	int frames = ofGetFrameNum();
	int modFrames = max(1, 60 / speed);
	if(frames % modFrames != 0)
	{
		return;
	}

	cellGeneration ++;

	bool accepted = false;
	while(!accepted)
	{
		copyToNext();
		applySingleCellRules();
		applyEntireGridRules();
		accepted = doesAcceptNewConfiguration();
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
	float cellWidth = screenwid / ((float) gridWidth);
	float cellHeight = screenhei / ((float) gridHeight);

	for(int x = 0; x < gridWidth; x++)
	{
		for(int y = 0; y < gridHeight; y++)
		{
			float coordx = (x + 0.5) * cellWidth;
			float coordy = (y + 0.5) * cellHeight;

			int decay, generation;
			int rel_decay = 255 / MAX_DECAY;
			int rel_generation = 255 / MAX_GENERATIONS;
			decay = GetCurrentConfigurationAt(x, y)->CellProperties.at("decay");
			generation = GetCurrentConfigurationAt(x, y)->CellProperties.at("generation");

			ofSetRectMode(OF_RECTMODE_CENTER);
			ofFill();

			//Border -- gets lighter as decays
			ofSetColor(decay * rel_decay);
			ofRect(coordx, coordy, 0, cellWidth, cellHeight);

			//white "background" square"
			ofSetColor(255);
			ofRect(coordx, coordy, 0, cellWidth * 0.8, cellHeight * 0.9);

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