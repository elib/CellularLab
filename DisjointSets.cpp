// Disjoint Set Data Structure
// Author: Emil Stefanov
// Date: 03/28/06
// Implementaton is as described in http://en.wikipedia.org/wiki/Disjoint-set_data_structure

#include <cassert>
#include "ofMain.h"

#ifdef WIN_32
#ifdef _DEBUG
#include <string>
using namespace std;
#include "windows.h"
#include <sstream>
#include <string>
#include <iostream>
#endif
#endif

#include "DisjointSets.h"


DisjointSets::DisjointSets()
{
	m_numElements = CELL_X*CELL_Y;
	for(int i = 0; i < m_numElements; i++)
		m_nodes[i] = NULL;


	Reset();
}

DisjointSets::~DisjointSets()
{
	for(int i = 0; i < m_numElements; ++i)
		delete m_nodes[i];
	m_numElements = 0;
	m_numSets = 0;
}

void DisjointSets::Reset()
{
	for(int i = 0; i < m_numElements; ++i)
	{
		if(m_nodes[i] == NULL)
			m_nodes[i] = new Node();

		m_nodes[i]->parent = NULL;
		m_nodes[i]->index = i;
		m_nodes[i]->rank = 0;
	}

	m_numSets = m_numElements;
}

// Note: some internal data is modified for optimization even though this method is consant.
int DisjointSets::FindSet(int elementId) const
{
	//assert(elementId < m_numElements);

	Node* curNode;

	// Find the root element that represents the set which `elementId` belongs to
	curNode = m_nodes[elementId % m_numElements];
	while(curNode->parent != NULL)
		curNode = curNode->parent;
	Node* root = curNode;

	// Walk to the root, updating the parents of `elementId`. Make those elements the direct
	// children of `root`. This optimizes the tree for future FindSet invokations.
	curNode = m_nodes[elementId % m_numElements];
	while(curNode != root)
	{
		Node* next = curNode->parent;
		curNode->parent = root;
		curNode = next;
	}

	return root->index;
}

void DisjointSets::Union(int setId1, int setId2)
{
	assert(setId1 < m_numElements);
	assert(setId2 < m_numElements);

	if(setId1 == setId2)
		return; // already unioned

	Node* set1 = m_nodes[setId1];
	Node* set2 = m_nodes[setId2];

	// Determine which node representing a set has a higher rank. The node with the higher rank is
	// likely to have a bigger subtree so in order to better balance the tree representing the
	// union, the node with the higher rank is made the parent of the one with the lower rank and
	// not the other way around.
	if(set1->rank > set2->rank)
		set2->parent = set1;
	else if(set1->rank < set2->rank)
		set1->parent = set2;
	else // set1->rank == set2->rank
	{
		set2->parent = set1;
		++set1->rank; // update rank
	}

	// Since two sets have fused into one, there is now one less set so update the set count.
	--m_numSets;
}

int DisjointSets::NumElements() const
{
	return m_numElements;
}

int DisjointSets::NumSets() const
{
	return m_numSets;
}

#ifdef WIN_32
#ifdef _DEBUG
void DisjointSets::DebugPrint(int wid, int hei)
{
	string s;
	ostringstream os;

	for(int j = 0; j < hei; j++)
	{
		for(int i = 0; i < wid; i++)
			os << this->FindSet(i + wid*j) << " ";
		os << "\n";
	}

	os << "\n";
	os << "\n";

	OutputDebugStringA(os.str().c_str());
}
#endif
#endif