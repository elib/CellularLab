#include "CellFactory.h"

#include "BaseCell.h"

#include "MegastructureCell.h"


CellFactory::CellFactory(void)
{
}


BaseCell* CellFactory::CreateBaseCell(CellTypes cellTypeToMake)
{

	switch(cellTypeToMake)
	{
	case MEGASTRUCTURE_CELL:
		return (new MegastructureCell());
	}

	return NULL;
}
