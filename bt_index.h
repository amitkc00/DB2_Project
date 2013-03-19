// 91574 Database II - C++ Programming
// Swathi Kurunji, UMass Lowell, MA, 2011
// bt_index.h - definition of class BtreeIndex.

#ifndef BT_INDEX_H
#define BT_INDEX_H

#include<iostream>
#include<cstdlib>
using namespace std;

#include "bt_node.h"
#include "bt_errors.h"

// BtreeIndex class defines the structure of B+tree index nodes
// BtreeIndex is derived from BtreeNode

class BtreeIndex : public BtreeNode{

public:
	BtreeIndex()
	{	
		set_type(INDEX);
		set_keyCount(0);
		//include all other initializations here
		//BtreeNode initializer should be called by default
	};

	~BtreeIndex(){};
		
	//insert key of type "KeyId", keyCount of type "int", leftChild and rightChild pointers of type BtreeNode*
	Status insertKey(KeyId, int, BtreeNode* leftChild, BtreeNode* rightChild);
	
	Status deleteKey(KeyId, int);
		
	Status searchKey(KeyId, int, BtreeNode* childPtr);

};

#endif
