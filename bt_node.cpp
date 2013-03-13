#include "bt_node.h"


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

BtreeNode::~BtreeNode(){}

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
