#pragma once

#include "BaseSingleCellRule.h"

class DecayingCellRule: public BaseSingleCellRule
{
public:
	DecayingCellRule(void);
	~DecayingCellRule(void);
	virtual void ApplyRule(class BaseCell* cell);
};

