// 91574 Database II - C++ Programming
// Swathi Kurunji, UMass Lowell, MA, 2011
// bt_leaf.h - definition of class BtreeLeaf.

#ifndef BT_LEAF_H
#define BT_LEAF_H

#include<iostream>
#include<cstdlib>
using namespace std;

#include "bt_node.h"
#include "bt_errors.h"

// BtreeLeaf class defines the structure of B+tree leaf nodes
// BtreeLeaf is derived from BtreeNode

class BtreeLeaf : public BtreeNode{

public:
	BtreeLeaf()
	{
		set_type(LEAF);
		set_keyCount(0);
		//include all other initializations here
	};

	~BtreeLeaf();
		
	//insert to node, key of type KeyId and keyCount-int
	Status insertKey(KeyId, int);

	Status deleteKey(KeyId, int);

	Status searchKey(KeyId, int *pos);
		

};

#endif
