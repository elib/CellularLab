#include "CellGrid.h"

#include "BaseCell.h"

CellGrid::CellGrid(void)
{
	//create new grid of cells
	_currentCells = new BaseCell*[10];
	for(int i = 0; i < 10; i++)
	{
		_currentCells[i] = new BaseCell[10];
	}
}

CellGrid::~CellGrid(void)
{
}
