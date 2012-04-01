#include "MegastructureCell.h"


MegastructureCell::MegastructureCell(void)
{
}


MegastructureCell::~MegastructureCell(void)
{
}

BaseCell* MegastructureCell::Copy()
{
	MegastructureCell* newcell = new MegastructureCell();
	for(unsigned int i = 0; i < CellProperties.size(); i++)
	{
		//copy properties
		//newcell->CellProperties
	}

	return newcell;
}