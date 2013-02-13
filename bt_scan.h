// 91574 Database II - C++ Programming
// Swathi Kurunji, UMass Lowell, MA, 2011
// bt_scan.h
 
#ifndef BT_SCAN_H
#define BT_SCAN_H

#include "bt_node.h"

class BtreeScan{

	BtreeNode *leaf;          // leaf page containing current record
	
	int pos; 		//This will be the current position of key which we need to scan 
				//This will be initially set to lo_key value and set to net key, each time we scan a key 
	
	KeyId endKey;          // if NULL, then go all the way right
				// else, stop when current key > this value.

public:
	BtreeScan();

 	// destructor
   	 ~BtreeScan();

	BtreeNode* get_leaf();

	Status set_leaf(BtreeNode *);

	int get_pos();

        Status set_pos(int);

	KeyId get_endKey();

        Status set_endKey(KeyId);


	// get the next record at position "pos" from node pointed by "leaf".
	Status getNext(KeyId *key);

    
};

#endif 
