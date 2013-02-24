#include "bt_node.h"


//TO DO - implement functions below. 

/*

        int type;               //can be index or leaf
        int keyCount;           //number of keys in the node

        KeyId key[MAX_NUM_KEYS];        //key of the record
        BtreeNode *ptr[MAX_NUM_PTRS];   //In leaf node pointers will be null

        BtreeNode *parentPtr;

*/

BtreeNode::BtreeNode(){
  
  int i ;

  type = 0;
  keyCount = 0;
  
  for( i = 0; i < MAX_NUM_PTRS; i++)
    ptr[i] = NULL;

  for(i = 0; i < MAX_NUM_KEYS; i++)
    key[i] = 0;

  parentPtr = NULL;

}

int BtreeNode::get_keyCount(){
  return keyCount;
}

void BtreeNode::set_keyCount(int x){
  keyCount = x;
}

void BtreeNode::set_type(int x){
  type = x;
}

int BtreeNode::get_type(){
  return type;
}

BtreeNode* BtreeNode::get_parentPtr(){
  return parentPtr;
}

void BtreeNode::set_parentPtr(BtreeNode *pointer){
  parentPtr = pointer;
}

/*
BtreeNode();

~BtreeNode();

int get_keyCount();

void set_keyCount(int);

//set type of node
void  set_type(int);

//get type of node. used while insertion, deletion or scan of record
int get_type();

BtreeNode* get_parentPtr();

void set_parentPtr(BtreeNode *pointer);
*/
