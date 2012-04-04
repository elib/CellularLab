#include "AssignResourcesRule.h"
#include <math.h>
#include "CellGrid.h"
#include "BaseCell.h"
#include "MegastructureConstants.h"

AssignResourcesRule::AssignResourcesRule(void)
{
}


AssignResourcesRule::~AssignResourcesRule(void)
{
}



void AssignResourcesRule::ApplyRule(CellGrid* grid)
{
	//in order to pump energy back into the system
	//and reduce decay in specific areas
	//assign "resources" to random cells?
	//(reduce decay and increase generation)

	int resources = 30;
	for(int i = 0; i < resources; i++)
	{
		int coordx = rand() % grid->gridWidth;
		int coordy = rand() % grid->gridHeight;

		BaseCell* cell = grid->GetNextConfigurationForEditAt(coordx, coordy);
		cell->CellProperties["decay"] = max(cell->CellProperties.at("decay") - 1, 0);
		cell->CellProperties["generation"] = min(cell->CellProperties.at("decay") + 1, MAX_GENERATIONS);

	}
}

BaseEntireGridRule* AssignResourcesRule::Copy()
{
	return new AssignResourcesRule(*this);
}