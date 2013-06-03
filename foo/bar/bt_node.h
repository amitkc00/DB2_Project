// File name : bt_node.h
// Date : 03/06/2013
// Team : Amit & Mike

#ifndef BT_NODE_H
#define BT_NODE_H

#include<iostream>
#include<cstdlib>
using namespace std;

#include "bt_errors.h"

// BtreeNode is the basic structure of B+tree nodes
// Each BtreeNode will be of one page size which is 1024

class BtreeNode{

protected:

	//NodeId nodeNo;  	//node number of the BtreeNode. 
	int type;   		//can be index or leaf
	int keyCount; 		//number of keys in the node

	KeyId key[MAX_NUM_KEYS];	//key of the record
	BtreeNode *ptr[MAX_NUM_PTRS]; 	//In leaf node pointers will be null

	BtreeNode *parentPtr;

public:
	BtreeNode();

	~BtreeNode();

	//void init();
	
	int get_keyCount();
	
	void set_keyCount(int);

	//set type of node
	void  set_type(int);
	
	//get type of node. used while insertion, deletion or scan of record
	int get_type();

	KeyId getKey(int n)
	{ return key[n]; }

	void setKey(KeyId keyID, int n)
	{ key[n] = keyID; }

	BtreeNode* getPtr(int n)
	{ return ptr[n]; }
		
	void setPtr(BtreeNode *pointer, int n)
	{ ptr[n] = pointer; }
	
	BtreeNode* get_parentPtr();

	void set_parentPtr(BtreeNode *pointer);

	//insert function with 4 parameters - needed for BtreeIndex 
	virtual Status insertKey(KeyId, BtreeNode* leftChild, BtreeNode* rightChild){
		cout<<"U r in wrong place"<<endl;
		return OK;
	}

	//insert function with 2 parameters - BtreeLeaf 
	virtual Status insertKey(KeyId, int){
		cout<<"U r in wrong place"<<endl;
		return OK;
	}

	virtual Status deleteKey(KeyId, int){
		cout<<"U r in wrong place"<<endl;
		return OK;
	}
	
	//search function with 3 parameters - needed for BtreeIndex, where childPtr will be set to the pointer on which we need to move downwards in tree	
	virtual Status searchKey(KeyId, int, BtreeNode** childPtr){
		cout<<"U r in wrong place"<<endl;
		return OK;
	}

	//search function with 2 parameters - BtreeLeaf
	virtual Status searchKey(KeyId, int*){
		cout<<"U r in wrong place"<<endl;
		return OK;
	}

};

#endif
