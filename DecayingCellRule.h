#pragma once

#include "BaseSingleCellRule.h"

class DecayingCellRule: public BaseSingleCellRule
{
public:
	DecayingCellRule(void);
	~DecayingCellRule(void);
	virtual void ApplyRule(class BaseCell* cell, class CellGrid* grid, int index_x, int index_y);
	virtual BaseSingleCellRule* Copy();
};

