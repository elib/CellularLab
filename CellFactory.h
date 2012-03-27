#pragma once

typedef enum __CELLTYPES
{
	MEGASTRUCTURE_CELL

} CellTypes;

class CellFactory
{
public:
	static class BaseCell* CreateBaseCell(CellTypes cellTypeToMake);
private:
	CellFactory(void);
};

