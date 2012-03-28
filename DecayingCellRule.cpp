#include "DecayingCellRule.h"

#include "BaseCell.h"
#include "CellGrid.h"


DecayingCellRule::DecayingCellRule(void)
{
}


DecayingCellRule::~DecayingCellRule(void)
{
}


void DecayingCellRule::ApplyRule(BaseCell* cell, CellGrid* grid, int index_x, int index_y)
{
}

BaseSingleCellRule* DecayingCellRule::Copy()
{
	return new DecayingCellRule();
}