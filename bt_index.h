// File name : bt_index.h
// Date : 03/06/2013
// Team : Amit & Mike

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
	Status insertKey(KeyId, BtreeNode* leftChild, BtreeNode* rightChild);
	
	Status deleteKey(KeyId, int);
		
	Status searchKey(KeyId, int, BtreeNode** childPtr);

};

#endif
