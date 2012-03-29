#include "AcceptIfConnectedRule.h"
#include "CellGrid.h"


AcceptIfConnectedRule::AcceptIfConnectedRule(void)
{
}


AcceptIfConnectedRule::~AcceptIfConnectedRule(void)
{
}


bool AcceptIfConnectedRule::AcceptRule(CellGrid* grid)
{

	return true;
}

BaseAcceptNewConfigRule* AcceptIfConnectedRule::Copy()
{
	return new AcceptIfConnectedRule();
}