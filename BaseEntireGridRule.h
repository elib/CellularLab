#pragma once

class CellGrid;

class BaseEntireGridRule
{
public:
	BaseEntireGridRule(void);
	~BaseEntireGridRule(void);


	virtual void ApplyRule(CellGrid* grid) = 0;
	virtual BaseEntireGridRule* Copy() = 0;

};