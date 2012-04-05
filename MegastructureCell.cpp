#include "MegastructureCell.h"
#include <math.h>


MegastructureCell::MegastructureCell(void)
{
	CellProperties["decay"] = rand() % 2;
	CellProperties["generation"] = rand() % 2;
	CellProperties["group"] = 0;
}


MegastructureCell::~MegastructureCell(void)
{
}

BaseCell* MegastructureCell::Copy()
{
	MegastructureCell* newcell = new MegastructureCell(*this);
	return newcell;
}