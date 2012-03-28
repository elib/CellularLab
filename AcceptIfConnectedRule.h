#pragma once

#include "BaseAcceptNewConfigRule.h"

class AcceptIfConnectedRule : public BaseAcceptNewConfigRule
{
public:
	AcceptIfConnectedRule(void);
	~AcceptIfConnectedRule(void);

	virtual bool AcceptRule(CellGrid* grid);
};

