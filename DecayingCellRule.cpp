#include "DecayingCellRule.h"

#include "BaseCell.h"
#include "CellGrid.h"

#include "MegastructureConstants.h"

DecayingCellRule::DecayingCellRule(void)
{
}


DecayingCellRule::~DecayingCellRule(void)
{
}


void DecayingCellRule::ApplyRule(BaseCell* cell, CellGrid* grid, int index_x, int index_y)
{
	int thisdecay = cell->CellProperties.at("decay");

	//count neighbors whose decay is greater than this
	int neighborcount = 0;
	for(int x = -1; x < 2; x++)
	{
		for(int y = -1; y < 2; y++)
		{
			if(!(x == 0 && y == 0))
			{
				neighborcount +=
					grid->GetCurrentConfigurationAt(index_x + x, index_y + y)->CellProperties.at("decay")
						> thisdecay ? 1 : 0;
			}
		}
	}

	if(neighborcount > 4)
	{
		//non-deterministic increase in decay
		int amount_to_increase = 2; //(rand() % 2) + 1;
		cell->CellProperties["decay"] = min(thisdecay + amount_to_increase, MAX_DECAY);
	}
	
}

BaseSingleCellRule* DecayingCellRule::Copy()
{
	return new DecayingCellRule(*this);
}