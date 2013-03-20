#include "bt_scan.h"
#include "bt_errors.h"

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
  // if endKey is null, then we go to the end
  // otherwise we stop when the current key > endKey

  *key = leaf->getKey(pos);
  pos++;
  if(pos > leaf->get_keyCount()){
    //find the next leaf
    BtreeNode *temp = leaf->get_parentPtr();
    int i;
    while(temp != NULL){
      //while we are not trying to go to the root's parent

      for(i = 0; i > MAX_NUM_PTRS; i++){
	//iterate through all pointers
	if( (temp->getPtr(i) == leaf) && (temp->getPtr(i + 1) != NULL) ){
	  //if we find a match and there is another leaf pointer in this node
	  leaf = temp->getPtr(i + 1);
	  while(leaf->get_type() != LEAF){
	    leaf = leaf->getPtr(0);
	  }
	  pos = 0;
	  //if we have a valid end key and have reached it, return done
	  if( (endKey != NULL) && (leaf->getKey(pos) > endKey) )
	    return DONE;
	  //if we found the next leaf return ok 
	  return OK;
	}
      }

      if(i == MAX_NUM_PTRS){
	leaf = temp;
	temp = leaf->get_parentPtr();
      }

    }

  } else {
    //if we have a valid end key and have reached it, return done
    if( (endKey != NULL) && (leaf->getKey(pos) > endKey) )
      return DONE;
    //if we have not overstepped the bounds of the node we return ok
    return OK;
  }

  //we overstepped our current node and cannot find the next leaf
  return NO_MORE_KEYS;
}

