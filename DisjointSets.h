// Disjoint Set Data Structure
// Author: Emil Stefanov
// Date: 03/28/06
// Implementaton is as described in http://en.wikipedia.org/wiki/Disjoint-set_data_structure
#pragma once
#include "CellConstants.h"


#define NODE_COUNT ((CELL_X + 2) * (CELL_Y + 2))

class DisjointSets
{
public:

	// Create an empty DisjointSets data structure
	DisjointSets();

	// Destructor
	~DisjointSets();

	// Find the set identifier that an element currently belongs to.
	// Note: some internal data is modified for optimization even though this method is constant.
	int FindSet(int element) const;
	// Combine two sets into one. All elements in those two sets will share the same set id that can be gotten using FindSet.
	void Union(int setId1, int setId2);
	// Returns the number of elements currently in the DisjointSets data structure.
	int NumElements() const;
	// Returns the number of sets currently in the DisjointSets data structure.
	int NumSets() const;

	void Reset();

#ifdef WIN_32
#ifdef _DEBUG
		void DebugPrint(int wid, int hei);
#endif
#endif

private:

	// Internal Node data structure used for representing an element
	struct Node
	{
		int rank; // This roughly represent the max height of the node in its subtree
		int index; // The index of the element the node represents
		Node* parent; // The parent node of the node
	};

	int m_numElements; // the number of elements currently in the DisjointSets data structure.
	int m_numSets; // the number of sets currently in the DisjointSets data structure.
	Node* m_nodes[NODE_COUNT]; // the list of nodes representing the elements
};