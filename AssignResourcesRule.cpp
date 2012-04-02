#include "AssignResourcesRule.h"


AssignResourcesRule::AssignResourcesRule(void)
{
}


AssignResourcesRule::~AssignResourcesRule(void)
{
}



void AssignResourcesRule::ApplyRule(CellGrid* grid)
{

}

BaseEntireGridRule* AssignResourcesRule::Copy()
{
	return new AssignResourcesRule(*this);
}