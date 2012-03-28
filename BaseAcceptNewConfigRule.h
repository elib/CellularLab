#pragma once

class CellGrid;

class BaseAcceptNewConfigRule
{
public:
	BaseAcceptNewConfigRule(void);
	~BaseAcceptNewConfigRule(void);

	virtual bool AcceptRule(CellGrid* grid) = 0;
};

