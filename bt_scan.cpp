#include "bt_scan.h"
#include "bt_errors.h"


/*
        BtreeNode *leaf;          // leaf page containing current record

        int pos;                //This will be the current position of key which we need to scan
                                //This will be initially set to lo_key value and set to net key, each time we scan a key

        KeyId endKey;          // if NULL, then go all the way right
                                // else, stop when current key > this value.

         ~BtreeScan();

        BtreeNode* get_leaf();
        Status set_leaf(BtreeNode *);
        int get_pos();
        Status set_pos(int);
        KeyId get_endKey();
        Status set_endKey(KeyId);
        // get the next record at position "pos" from node pointed by "leaf".
        Status getNext(KeyId *key);

*/

BtreeScan::~BtreeScan(){
  //cleanup
}

BtreeNode* BtreeScan::get_leaf(){
  return leaf;
}

Status BtreeScan::set_leaf(BtreeNode *x){
  leaf = x;
  return OK;
}

int BtreeScan::get_pos(){
  return pos;
}

Status BtreeScan::set_pos(int x){
  pos = x;
  return OK;
}

KeyId BtreeScan::get_endKey(){
  return endKey;
}

Status BtreeScan::set_endKey(KeyId x){
  endKey = x;
  return OK;
}

Status BtreeScan::getNext(KeyId *key){

  //we are in node "leaf" at position "pos" 
  //based on the end key, we iterate through
  // if endKey is null, the node is full so we go to the end
  // otherwise we stop when the current key > endKey

  // we get the next leaf node by saving the current key, going to the parent,
  // seeing if it has the pointer to the next leaf, if not keep going up until
  // we find the next leaf node which has the next key.

  return OK;
}

