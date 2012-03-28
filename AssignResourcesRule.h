#pragma once

#include "BaseEntireGridRule.h"

class AssignResourcesRule : public BaseEntireGridRule
{
public:
	AssignResourcesRule(void);
	~AssignResourcesRule(void);


	virtual void ApplyRule(CellGrid* grid);
};

