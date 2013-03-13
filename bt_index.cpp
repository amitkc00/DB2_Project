#include "bt_index.h"
#include "bt_errors.h"




/*
        //insert key of type "KeyId", keyCount of type "int", leftChild and rightChild pointers of type BtreeNode*
        Status insertKey(KeyId, int, BtreeNode*& leftChild, BtreeNode*& rightChild);

        Status deleteKey(KeyId, int);

        Status searchKey(KeyId, int, BtreeNode*& childPtr);
*/

Status BtreeIndex::insertKey(KeyId key, int count, BtreeNode* leftChild, BtreeNode* rightChild){
  //insert key into array at index count, insert leftChild at index count and rightChild at index count + 1
  setKey(key, count);
  setPtr(leftChild, count);
  setPtr(rightChild, count + 1);
  /*  
  int tcount = get_keyCount();
  int i;
  tcount += count;
  if(tcount > MAX_NUM_KEYS)
    return INDEX_IS_FULL;
  set_keyCount(tcount);
  for(i = 0; i < tcount; i++){
    if( (i == 0) && (getKey(i) > key) ){
      //insert into front of array
      KeyId temp_key = key;
      KeyId temp_key2;
      for(; i > tcount; i++){
	temp_key2 = getKey(i);
	setKey(i, temp_key);
	temp_key = temp_key2;
      }
      return OK;
    } else if(i + 1 == tcount){
      //insert into end
      setKey(key, tcount);
      return OK;
    } else if ( (getKey(i) < key) && (getKey(i+1) > key) ){
      //insert at i+1
      KeyId temp_key = key;
      KeyId temp_key2;
      i++;
      for(; i > tcount; i++){
	temp_key2 = getKey(i);
	setKey(i, temp_key);
	temp_key = temp_key2;
      }
      return OK;
    }
    }*/
  return FAIL;
}

Status BtreeIndex::deleteKey(KeyId key, int count){
  return OK;
}

Status BtreeIndex::searchKey(KeyId key, int count, BtreeNode* childPtr){
  int i;
  BtreeNode *child;
  int num_keys = get_keyCount();
  for(i = 0; i < num_keys; i++){
    if(i == num_keys){
      if(getKey(i) > key){
	//left pointer
	child = getPtr(i+1);
	*childPtr = *child;
	return child->searchKey(key, count);
      }
      //right pointer
      child = getPtr(i+1);
      *childPtr = *child;
      return child->searchKey(key, count);
    } else if( (i == 0) && (getKey(i) > key) ){
      //left pointer
      child = getPtr(i);
      *childPtr = *child;
      return child->searchKey(key, count);
    } else if ( (getKey(i-1) < key) && (getKey(i) > key) ){
      //left pointer
      child = getPtr(i);
      *childPtr = *child;
      return child->searchKey(key, count);
    }
  }
  return FAIL;
}



