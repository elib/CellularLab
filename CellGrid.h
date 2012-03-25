#pragma once

class BaseCell;

class CellGrid
{
public:


	CellGrid(void);
	~CellGrid(void);

private:
	BaseCell ** _currentCells;
	BaseCell ** _nextCells;
};

