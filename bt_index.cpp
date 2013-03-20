// File name : bt_index.cpp
// Date : 03/06/2013
// Team : Amit & Mike

#include "bt_index.h"
#include "bt_errors.h"


Status BtreeIndex::insertKey(KeyId key, int count, BtreeNode* leftChild, BtreeNode* rightChild){
  //insert key into array at index count, insert leftChild at index count and rightChild at index count + 1

  KeyId current_keyCount = get_keyCount();

  if (current_keyCount == MAX_NUM_KEYS){
    //index node is full

    return INDEX_IS_FULL;
  } else {
    //parse list

    int i, j; 

    for(i = 0; i < MAX_NUM_KEYS; i++){
      if (getKey(i) == -1) {
	//end of the list

	setKey(key, i);
	setPtr(leftChild, i);
	setPtr(rightChild, i + 1);
	set_keyCount(current_keyCount + 1);
	return OK;

      } else if ((i == 0) && (getKey(i) > key)){
	//beginning of the list
	
	//shift everything before me to the right
	for(j = current_keyCount + 1; j > i; j--){
	  setKey(getKey(j-1), j);
	  setPtr(getPtr(j), j + 1);
	}
	//once shifted, I can insert in-place
	setKey(key, i);
	setPtr(leftChild, i);
	setPtr(rightChild, i + 1);	  
	set_keyCount(current_keyCount + 1);
	return OK;

      } else if( (getKey(i - 1) < key) && (getKey(i) > key) ){
	//middle of the list

	//shift everything before me to the right
	for(j = current_keyCount + 1; j > i; j--){
	  setKey(getKey(j-1), j);
	  setPtr(getPtr(j), j + 1);
	}
	//once shifted, I can insert in-place
	setKey(key, i);
	setPtr(leftChild, i);
	setPtr(rightChild, i + 1);	  
	set_keyCount(current_keyCount + 1);
	return OK;
      }
    }
  }

  //should never get here
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
      //end of the list

      if(getKey(i) > key){
	//left pointer
	child = getPtr(i+1);
	*childPtr = *child;
	return OK;
      }

      //right pointer
      child = getPtr(i+1);
      *childPtr = *child;
      return OK;

    } else if( (i == 0) && (getKey(i) > key) ){
      //beginning of the list

      //left pointer
      child = getPtr(i);
      *childPtr = *child;
      return OK;

    } else if ( (getKey(i-1) < key) && (getKey(i) > key) ){
      //in middle of list

      //left pointer
      child = getPtr(i);
      *childPtr = *child;
      return OK;
    }
  }

  //should never get here
  return FAIL;
}



