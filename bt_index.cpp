#include "bt_index.h"
#include "bt_errors.h"




/*
        //insert key of type "KeyId", keyCount of type "int", leftChild and rightChild pointers of type BtreeNode*
        Status insertKey(KeyId, int, BtreeNode*& leftChild, BtreeNode*& rightChild);

        Status deleteKey(KeyId, int);

        Status searchKey(KeyId, int, BtreeNode*& childPtr);
*/

Status BtreeIndex::insertKey(KeyId key, int count, BtreeNode* leftChild, BtreeNode* rightChild){
  return OK;
}

Status BtreeIndex::deleteKey(KeyId key, int count){
  return OK;
}

Status BtreeIndex::searchKey(KeyId key, int count, BtreeNode* childPtr){
  return OK;
}



