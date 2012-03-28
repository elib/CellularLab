#pragma once
class BaseSingleCellRule
{
public:
	BaseSingleCellRule(void);
	~BaseSingleCellRule(void);

	virtual void ApplyRule(class BaseCell* cell) = 0; 
};