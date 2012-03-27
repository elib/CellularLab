#pragma once

#include "CellFactory.h"

class BaseCell;
class BaseSingleCellRule;
class BaseEntireGridRule;
class BaseAcceptNewConfigRule;

class CellGrid
{
public:


	CellGrid(void);
	~CellGrid(void);

	void Update();
	void Setup(CellTypes typeToCreate);

	void AddCellRule(BaseSingleCellRule* newRule);
	void AddGlobalRule(BaseEntireGridRule* newRule);
	void AddAcceptRule(BaseAcceptNewConfigRule* newRule);

private:
	BaseCell ** _currentCells;
	BaseCell ** _nextCells;
};

