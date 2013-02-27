#include "bt_scan.h"
#include "bt_errors.h"


/*
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
  BtreeNode *temp = (BtreeNode*)malloc(sizeof(BtreeNode));
  return temp;
}

Status BtreeScan::set_leaf(BtreeNode *x){
  return OK;
}

int BtreeScan::get_pos(){
  return 0;
}

Status BtreeScan::set_pos(int x){
  return OK;
}

KeyId BtreeScan::get_endKey(){
  return 0;
}

Status BtreeScan::set_endKey(KeyId x){
  return OK;
}

Status BtreeScan::getNext(KeyId *key){
  return OK;
}

/*
        BtreeNode *leaf;          // leaf page containing current record

        int pos;                //This will be the current position of key which we need to scan
                                //This will be initially set to lo_key value and set to net key, each time we scan a key

        KeyId endKey;          // if NULL, then go all the way right
                                // else, stop when current key > this value.
				
*/

