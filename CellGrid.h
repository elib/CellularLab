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
	void Setup(CellTypes typeToCreate);


	void AddCellRule(BaseSingleCellRule* newRule);
	void AddGlobalRule(BaseEntireGridRule* newRule);
	void AddAcceptRule(BaseAcceptNewConfigRule* newRule);

	BaseCell ** _currentCells;
	BaseCell ** _nextCells;

private:

	void InitCells(CellTypes cellTypeToCreate, BaseCell*** targetGrid);

	SingleCellRuleList _singleCellRules;
	EntireGridRuleList _entireGridRules;
	AcceptNewConfigRuleList _acceptNewConfigRules;
};

