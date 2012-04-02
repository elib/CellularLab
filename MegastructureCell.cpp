#include "MegastructureCell.h"
#include <math.h>


MegastructureCell::MegastructureCell(void)
{
	CellProperties["decay"] = rand() % 10;
	CellProperties["generation"] = rand() % 10;
}


MegastructureCell::~MegastructureCell(void)
{
}

BaseCell* MegastructureCell::Copy()
{
	MegastructureCell* newcell = new MegastructureCell(*this);
	return newcell;
}