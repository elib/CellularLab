#include "CellGrid.h"

#include "BaseCell.h"

#include "BaseAcceptNewConfigRule.h"
#include "BaseEntireGridRule.h"
#include "BaseSingleCellRule.h"

CellGrid::CellGrid(void)
{

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
}

void CellGrid::AddAcceptRule(BaseAcceptNewConfigRule* newRule)
{
}


void CellGrid::InitCells(CellTypes cellTypeToCreate, BaseCell*** targetGrid)
{
	//create new grid of cells
	(*targetGrid) = new BaseCell*[10];
	for(int i = 0; i < 10; i++)
	{
		(*targetGrid)[i] = CellFactory::CreateBaseCell(cellTypeToCreate);
	}
}


void CellGrid::Setup(CellTypes cellTypeToCreate)
{
	InitCells(cellTypeToCreate, &_currentCells);
	InitCells(cellTypeToCreate, &_nextCells);
}

void CellGrid::Update()
{
}

void CellGrid::Draw()
{

}