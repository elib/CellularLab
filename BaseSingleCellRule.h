#pragma once
class BaseSingleCellRule
{
public:
	virtual ~BaseSingleCellRule(void);

	virtual void ApplyRule(class BaseCell* cell, class CellGrid* grid, int index_x, int index_y) = 0;

	virtual BaseSingleCellRule* Copy() = 0;
};