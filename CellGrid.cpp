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
}

void CellGrid::AddGlobalRule(BaseEntireGridRule* newRule)
{
}

void CellGrid::AddAcceptRule(BaseAcceptNewConfigRule* newRule)
{
}


void CellGrid::Setup(CellTypes cellTypeToCreate)
{
	//create new grid of cells
	_currentCells = new BaseCell*[10];
	for(int i = 0; i < 10; i++)
	{
		_currentCells[i] = CellFactory::CreateBaseCell(cellTypeToCreate);
	}

}

void CellGrid::Update()
{
}