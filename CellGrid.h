#pragma once

#include "CellFactory.h"
#include <vector>

using namespace std;

class BaseCell;
class BaseSingleCellRule;
class BaseEntireGridRule;
class BaseAcceptNewConfigRule;


typedef vector<BaseSingleCellRule*> SingleCellRuleList;
typedef vector<BaseEntireGridRule*> EntireGridRuleList;
typedef vector<BaseAcceptNewConfigRule*> AcceptNewConfigRuleList;


class CellGrid
{
public:

	CellGrid(void);
	~CellGrid(void);

	void Update(int speed);
	void Draw(int screenwid, int screenhei);
	void Setup(CellTypes typeToCreate, int width, int height);


	void AddCellRule(BaseSingleCellRule* newRule);
	void AddGlobalRule(BaseEntireGridRule* newRule);
	void AddAcceptRule(BaseAcceptNewConfigRule* newRule);

	const BaseCell* GetCurrentConfigurationAt(int x, int y);
	const BaseCell* GetCurrentConfigurationEffectiveAt(int x, int y);
	const BaseCell* GetNextConfigurationAt(int x, int y);
	const BaseCell* GetNextConfigurationEffectiveAt(int x, int y);
	BaseCell* GetNextConfigurationForEditAt(int x, int y);
	

	int gridWidth, gridHeight;

	int cellGeneration;

	int total_decay;

private:

	//inside the grid
	BaseCell *** _currentCells;
	BaseCell *** _nextCells;

	//handle grid edges here
	BaseCell ** _edges;

	void copyToTarget(BaseCell *** source, BaseCell *** target);
	void copyToNext();
	void applySingleCellRules();
	void applyEntireGridRules();
	bool doesAcceptNewConfiguration();

	const BaseCell* getCell(BaseCell*** target, int x, int y);
	const BaseCell* getEffectiveCell(BaseCell*** target, int x, int y);
	BaseCell* getCellForEdit(BaseCell*** target, int x, int y);

	void InitCells(CellTypes cellTypeToCreate, BaseCell**** targetGrid);

	SingleCellRuleList _singleCellRules;
	EntireGridRuleList _entireGridRules;
	AcceptNewConfigRuleList _acceptNewConfigRules;
};

