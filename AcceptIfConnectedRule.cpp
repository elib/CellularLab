#include "AcceptIfConnectedRule.h"
#include "CellGrid.h"

#include "DisjointSets.h"
#include "BaseCell.h"

AcceptIfConnectedRule::AcceptIfConnectedRule(void)
{
}


AcceptIfConnectedRule::~AcceptIfConnectedRule(void)
{
}


bool AcceptIfConnectedRule::AcceptRule(CellGrid* grid)
{
	//set up disjoint sets
	DisjointSets sets;
	for(int x = 0; x < grid->gridWidth; x++)
	{
		for(int y = 0; y < grid->gridHeight; y++)
		{
			//each cell: connect to neighbors on right-bottom sides
			int thisdecay = grid->GetNextConfiguratonAt(x, y)->CellProperties.at("decay");
			int rightdecay = grid->GetNextConfiguratonAt(x + 1, y)->CellProperties.at("decay");
			int belowdecay = grid->GetNextConfiguratonAt(x, y + 1)->CellProperties.at("decay");

			//to be connected to a neighbor:
			// * you must be relatively closely decayed
			// * both sides must be below a certain decay threshold
			int maxDecay = 10;

			if(thisdecay <= maxDecay)
			{
				int maxDecayDiff = 5;
				if(abs(thisdecay - rightdecay) <= maxDecayDiff)
				{
					if(rightdecay <= maxDecay)
					{
						sets.Union(sets.FindSet(x + grid->gridWidth * y), sets.FindSet((x+1) + grid->gridWidth * y));
					}

					if(abs(thisdecay - belowdecay) <= maxDecayDiff)
					{
						if(belowdecay <= maxDecay)
						{
							sets.Union(sets.FindSet(x + grid->gridWidth * y), sets.FindSet(x + grid->gridWidth * (y+1)));
						}
					}
				}
			}
		}
	}

	//try to connect the four cardinal directions?
	int setTop = sets.FindSet(CELL_X/2);
	int setBottom = sets.FindSet(CELL_X/2 + grid->gridWidth*(CELL_Y - 1));
	int setLeft = sets.FindSet(0 + grid->gridWidth*(CELL_Y/2));
	int setRight = sets.FindSet((CELL_X - 1) + grid->gridWidth*(CELL_Y/2));
	//if(CELL_X % 2 != 0)
	//{
	//	sets.Union(setTop, sets.FindSet(CELL_X/2 - 1));
	//	sets.Union(setBottom, sets.FindSet(CELL_X/2 + grid->gridWidth*(CELL_Y - 1) - 1));
	//}
	//if(CELL_Y % 2 != 0)
	//{
	//	sets.Union(setLeft, sets.FindSet(grid->gridWidth*(CELL_Y/2 - 1)));
	//	sets.Union(setRight, sets.FindSet((CELL_X - 1) + grid->gridWidth*(CELL_Y/2 - 1)));
	//}


	if (setTop == setBottom && setBottom == setLeft && setLeft == setRight)
	{
		return true;
	}


	return false;
}

BaseAcceptNewConfigRule* AcceptIfConnectedRule::Copy()
{
	return new AcceptIfConnectedRule(*this);
}