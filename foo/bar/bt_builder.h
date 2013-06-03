// 91574 Database II - C++ Programming
// Swathi Kurunji, UMass Lowell, MA, 2011
// bt_builder.h - definition of class BtreeBuilder for this project.

#ifndef BT_BUILDER_H
#define BT_BUILDER_H

#include<iostream>
#include<cstdlib>
using namespace std;

#include "bt_errors.h"
#include "bt_node.h"
#include "bt_leaf.h"
#include "bt_index.h"
#include "bt_scan.h"

class BtreeBuilder{

	BtreeNode *root;   //will point to root of the tree

public:
	BtreeBuilder()
	{
		BtreeLeaf * btl = new BtreeLeaf();
		root = btl;
	};

	~BtreeBuilder();
	
	friend class BtreeScan;

	//this function inserts key into B+ tree
	//this traverses from root until leaf node is reached. 
	//inserts the key. If required splits node and propagates the split 
	//until a node which does not need split is reached
	Status insertBuilderKey(KeyId);
	
	//deletes the specified key from the tree
	Status deleteBuilderKey(KeyId);

	//1st argument(arg) is the key that we need to insert 
	//In 2nd arg, we store the key value that we need to insert in parent node after splitting node
	//3rd is the node which is full and needs split
	//4th and 5th holds the new left and right child address(we need to store this in parent node)
	Status splitNode(KeyId, BtreeNode *, BtreeNode *, BtreeNode *);


	// create a scan with given keys
	// Cases:
	//      (1) lo_key = NULL, hi_key = NULL
	//              scan the whole index
	//      (2) lo_key = NULL, hi_key!= NULL
	//              range scan from min to the hi_key
	//      (3) lo_key!= NULL, hi_key = NULL
	//              range scan from the lo_key to max
	//      (4) lo_key!= NULL, hi_key!= NULL, lo_key = hi_key
	//              exact match ( might not unique)
	//      (5) lo_key!= NULL, hi_key!= NULL, lo_key < hi_key
	//              range scan from lo_key to hi_key
	BtreeScan* openScan(KeyId lo_key = NULL, KeyId hi_key = NULL);


	//find the starting position.
	//scanTree function calls this function by passing lo_key to find the starting position in the B+tree.
	//input are: pointer of scan object and lo_key
	Status findStartPosition(BtreeScan *,KeyId);

	//This function recursively deletes the whole B+tree
	Status destroyBtree();

};

#endif
