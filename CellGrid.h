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

	void Update();
	void Draw();
	void Setup(CellTypes typeToCreate, int width, int height);


	void AddCellRule(BaseSingleCellRule* newRule);
	void AddGlobalRule(BaseEntireGridRule* newRule);
	void AddAcceptRule(BaseAcceptNewConfigRule* newRule);

	const BaseCell *** CurrentConfiguration();

	int gridWidth, gridHeight;

private:

	BaseCell *** _currentCells;
	BaseCell *** _nextCells;

	void copyToTarget(BaseCell *** source, BaseCell *** target);
	void copyToNext();
	void applySingleCellRules();
	void applyEntireGridRules();
	bool doesAcceptNewConfiguration();

	void InitCells(CellTypes cellTypeToCreate, BaseCell**** targetGrid);

	SingleCellRuleList _singleCellRules;
	EntireGridRuleList _entireGridRules;
	AcceptNewConfigRuleList _acceptNewConfigRules;
};

