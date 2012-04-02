#include "DecayingCellRule.h"

#include "BaseCell.h"
#include "CellGrid.h"


#define MAX_DECAY 10

DecayingCellRule::DecayingCellRule(void)
{
}


DecayingCellRule::~DecayingCellRule(void)
{
}


void DecayingCellRule::ApplyRule(BaseCell* cell, CellGrid* grid, int index_x, int index_y)
{
		/*int thisdecay = cell->CellProperties.at("decay");
		cell->CellProperties["decay"] = thisdecay + 1;
*/


	int thisdecay = cell->CellProperties.at("decay");
		
	//count neighbors whose decay is greater than this
	int neighborcount = 0;
	neighborcount += grid->GetCurrentConfigurationAt(index_x - 1, index_y)->CellProperties.at("decay") > thisdecay ? 1 : 0;
	neighborcount += grid->GetCurrentConfigurationAt(index_x + 1, index_y)->CellProperties.at("decay") > thisdecay ? 1 : 0;
	neighborcount += grid->GetCurrentConfigurationAt(index_x - 1, index_y - 1)->CellProperties.at("decay") > thisdecay ? 1 : 0;
	neighborcount += grid->GetCurrentConfigurationAt(index_x + 1, index_y - 1)->CellProperties.at("decay") > thisdecay ? 1 : 0;
	neighborcount += grid->GetCurrentConfigurationAt(index_x - 1, index_y + 1)->CellProperties.at("decay") > thisdecay ? 1 : 0;
	neighborcount += grid->GetCurrentConfigurationAt(index_x + 1, index_y + 1)->CellProperties.at("decay") > thisdecay ? 1 : 0;
	neighborcount += grid->GetCurrentConfigurationAt(index_x, index_y - 1)->CellProperties.at("decay") > thisdecay ? 1 : 0;
	neighborcount += grid->GetCurrentConfigurationAt(index_x, index_y + 1)->CellProperties.at("decay") > thisdecay ? 1 : 0;

	//float neighborweight = neighborsum / 8.0f; //how heavy is the neighborhood
	//int thisdecay = cell->CellProperties.at("decay");

	if(neighborcount > 4)
	{
		cell->CellProperties["decay"] = min(thisdecay + 2, MAX_DECAY);
	}
	
}

BaseSingleCellRule* DecayingCellRule::Copy()
{
	return new DecayingCellRule(*this);
}