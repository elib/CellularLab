#include "CellGrid.h"

#include "BaseCell.h"

#include "BaseAcceptNewConfigRule.h"
#include "BaseEntireGridRule.h"
#include "BaseSingleCellRule.h"

#include "ofMain.h"

CellGrid::CellGrid(void)
{
	gridWidth = 0;
	gridHeight = 0;
	
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

const BaseCell *** CellGrid::CurrentConfiguration()
{
	return (const BaseCell***)_currentCells;
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

void CellGrid::Update()
{
	//decide if another generation is necessary (else exit)
	int frames = ofGetFrameNum();
	if(frames % 60 != 0)
	{
		return;
	}

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
	for(int i = 0; i < _entireGridRules.size(); i++)
	{
		_entireGridRules[i]->ApplyRule(this);
	}
}

bool CellGrid::doesAcceptNewConfiguration()
{
	return true;
}

void CellGrid::copyToNext()
{
	//copy next generation into current generation
	copyToTarget(_currentCells, _nextCells);
}

void CellGrid::Draw()
{
	//run over current generation and draw them
}