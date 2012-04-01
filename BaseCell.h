#pragma once

#include <string>
#include <map>

using namespace std;

typedef map<string, int> PropertyList;

class BaseCell
{
public:
	BaseCell(void);
	~BaseCell(void);

	virtual BaseCell* Copy() = 0;

	PropertyList CellProperties;
};