// File Name : bt_builder.cpp
// Date : 03/06/2013
// Team : Amit & Mike


#include "bt_builder.h"


BtreeBuilder::~BtreeBuilder(){
  //destroyBtree();
}


Status BtreeBuilder::insertBuilderKey(KeyId KeyValue) {
	Status ret;
	//Step 1 : Find the Child Pointer the KeyId needs to be inserted.
	const int type = root->get_type();
	if (type == LEAF) {
		// Traverse this node and insert your value
		ret = root->insertKey(KeyValue,0) ; // As defined in bt_node.cpp
		if (ret == LEAF_IS_FULL) {
			ret = splitNode(KeyValue,root,root->getPtr(MAX_NUM_KEYS-1),root->getPtr(MAX_NUM_KEYS));
			if (ret != OK)
				return FAIL;
		}	
		else if (ret != OK)
			return FAIL;
	}
	else {
		BtreeNode *temp = new BtreeIndex;
		//BtreeIndex *temp;  //NEED TO MAKE SURE IF THIS IS RIGHT DEFINITION
		root->searchKey(KeyValue,0,&temp);
		while(temp->get_type() != LEAF){
			temp->searchKey(KeyValue,0,&temp);
		}
		ret = temp->insertKey(KeyValue,0);
		if (ret == LEAF_IS_FULL) {
			ret = splitNode(KeyValue,temp,temp->getPtr(MAX_NUM_KEYS-1),temp->getPtr(MAX_NUM_KEYS));
			if (ret != OK)
				return FAIL;
		}	
		else if (ret != OK)
		return FAIL;
	}
	return OK; 
}

Status BtreeBuilder::deleteBuilderKey(KeyId) {
	return OK;
}

Status BtreeBuilder::splitNode(KeyId KeyValue, BtreeNode * FullNode_Ptr, BtreeNode * lChild_Ptr, BtreeNode * rChild_Ptr) {
	Status ret;
	if (FullNode_Ptr->get_type() == LEAF) {
		//BtreeNode *New_SplitNode;
	  BtreeLeaf *New_SplitNode = new BtreeLeaf ;
	  //New_SplitNode->set_type(LEAF); //FIND OUT IF WE NEED IT TEST
		for (int i = MAX_NUM_KEYS/2 ; i < MAX_NUM_KEYS ; i++) {
			ret = New_SplitNode->insertKey(FullNode_Ptr->getKey(i),0);
			if(ret != OK)
				return FAIL;
			FullNode_Ptr->setKey(-1,i);
			FullNode_Ptr->set_keyCount(FullNode_Ptr->get_keyCount()-1);
		}
		if(New_SplitNode->getKey(0) >  KeyValue){
		  //greater
		  ret = FullNode_Ptr->insertKey(KeyValue,0);
		}else {
		  //= or less
		  ret = New_SplitNode->insertKey(KeyValue,0);
		}
		if(ret != OK)
			return FAIL;

		if (FullNode_Ptr == root) {
			BtreeNode *New_IndexNode = new BtreeIndex; //TEST if this is correct.
			//BtreeIndex New_IndexNode;
			New_IndexNode->set_type(INDEX); //FIND OUT IF WE STILL NEED IT TEST
			ret = New_IndexNode->insertKey(New_SplitNode->getKey(0), FullNode_Ptr, New_SplitNode);
			if (ret == OK){
			        FullNode_Ptr->set_parentPtr(New_IndexNode);
				New_SplitNode->set_parentPtr(New_IndexNode);
				root = New_IndexNode;
			} else
				return FAIL;
		}
		else { // When it is not root, we need to insert entry for new leaf node in parent node.
			//ret = (FullNode_Ptr->get_parentPtr())->insertKey(New_IndexNode->getKey(0),count, FullNode_Ptr, New_IndexNode);
			ret = (FullNode_Ptr->get_parentPtr())->insertKey(New_SplitNode->getKey(0), FullNode_Ptr, New_SplitNode);
			if (ret != OK && ret != INDEX_IS_FULL)
				return FAIL;
			else if (ret == INDEX_IS_FULL) {  // This is a recursive call to splitNode to handle this case.
				ret = splitNode(New_SplitNode->getKey(0),FullNode_Ptr->get_parentPtr(),FullNode_Ptr, New_SplitNode);
				//New_SplitNode above may need Change. TEST
				if (ret != OK)
					return FAIL;
			}else if (ret == OK){
			        FullNode_Ptr->set_parentPtr(FullNode_Ptr->get_parentPtr());
			        New_SplitNode->set_parentPtr(FullNode_Ptr->get_parentPtr());
			} else
			        return FAIL;
		}
		return OK;
	} else if (FullNode_Ptr->get_type() == INDEX) {
		BtreeNode *New_IndexNode = new BtreeIndex;
		//BtreeIndex New_IndexNode;
		New_IndexNode->set_type(INDEX); //TEST IF WE REALLY NEED IT.
		int i;
		for (i = MAX_NUM_KEYS/2 ; i < MAX_NUM_KEYS ; i++) {
			ret = New_IndexNode->insertKey(FullNode_Ptr->getKey(i), FullNode_Ptr->getPtr(i), FullNode_Ptr->getPtr(i+1));
			if(ret != OK)
				return FAIL;
			FullNode_Ptr->setKey(-1,i);
			//FullNode_Ptr->setPtr(NULL,i);
			//Since keys share children we cannot clear i+1 until the end.
			//FullNode_Ptr->setPtr(NULL,i+1);
			FullNode_Ptr->set_keyCount(FullNode_Ptr->get_keyCount()-1);
		}
		for (i = MAX_NUM_KEYS/2 ; i < MAX_NUM_KEYS ; i++) {
		        //we set the right pointers to null
		        FullNode_Ptr->setPtr(NULL,i+1);
		}
		Status ret;
		if( New_IndexNode->getKey(0) > KeyValue ){
		  //less than
		  // lChild_Ptr, BtreeNode * rChild_Ptr
		  ret = FullNode_Ptr->insertKey(KeyValue, lChild_Ptr, rChild_Ptr);
		  lChild_Ptr->set_parentPtr(FullNode_Ptr);
		  rChild_Ptr->set_parentPtr(FullNode_Ptr);
		} else{
		  //greater than or =
		  ret = New_IndexNode->insertKey(KeyValue, lChild_Ptr, rChild_Ptr);
		  lChild_Ptr->set_parentPtr(New_IndexNode);
		  rChild_Ptr->set_parentPtr(New_IndexNode);
		}
		if (ret != OK)
			return FAIL;

		KeyId parent_insert = New_IndexNode->getKey(0);
		//shift on the right node has not been done yet
		for (int i = 0 ; i < MAX_NUM_KEYS ; i++) {
		  New_IndexNode->setKey(New_IndexNode->getKey(i+1),i);
		  New_IndexNode->setPtr(New_IndexNode->getPtr(i+1),i);
		}
		New_IndexNode->set_keyCount(New_IndexNode->get_keyCount()-1);

		if (FullNode_Ptr == root) { //If Full Index Node was root, we create a new Index node and mark it as root after moving our first pointer fron New_IndexNode to it.
			BtreeNode *New_IndexNode_root = new BtreeIndex;
			//BtreeIndex New_IndexNode_root;
			ret = New_IndexNode_root->insertKey(parent_insert, FullNode_Ptr,New_IndexNode);
			if (ret != OK)
				return FAIL;
			if (ret == OK) {
			        FullNode_Ptr->set_parentPtr(New_IndexNode_root);
				New_IndexNode->set_parentPtr(New_IndexNode_root);
				root = New_IndexNode_root;
			}
		}
		else {
			//ret = (FullNode_ptr->get_parentPtr())->insertKey(NewSplitNode->getKey(0),int count, FullNode_ptr, New_SplitNode);
			ret = (FullNode_Ptr->get_parentPtr())->insertKey(parent_insert, FullNode_Ptr, New_IndexNode);
			if (ret != OK && ret != INDEX_IS_FULL)
				return FAIL;
			else if (ret == INDEX_IS_FULL) {
				ret = splitNode(parent_insert, FullNode_Ptr->get_parentPtr(),FullNode_Ptr,New_IndexNode);
				if (ret != OK)
					return FAIL;		
			}
			else if (ret == OK){
			        FullNode_Ptr->set_parentPtr(FullNode_Ptr->get_parentPtr());
			        New_IndexNode->set_parentPtr(FullNode_Ptr->get_parentPtr());
			} else
				return FAIL;
		}
		return OK;
		//Create a New Root Node because of Index Node Split and Take the first element from New_IndexNode and move it to Parent Nod.
	}
	return FAIL;
}		


BtreeScan* BtreeBuilder::openScan(KeyId lo_key, KeyId hi_key) {

  // Cases:
  //      (1) lo_key = NULL, hi_key = NULL
  //              scan the whole index
  //      (2) lo_key = NULL, hi_key!= NULL
  //              range scan from min to the hi_key
  //      (3) lo_key!= NULL, hi_key = NULL
  //              range scan from the lo_key to max
  //      (4) lo_key!= NULL, hi_key!= NULL, lo_key = hi_key
  //              exact match ( might not unique)
  //      (5) lo_key!= NULL, hi_key!= NULL, lo_key < hi_key
  //              range scan from lo_key to hi_key

  BtreeScan *scan = new BtreeScan();

  BtreeNode *current = root;
  BtreeNode *tmp;

  int leaf_pos;

  if(lo_key == NULL){
    scan->set_pos(0);
    while(current->get_type() != LEAF){
      current->searchKey(-1, 0, &tmp);
      current = tmp;
    }
  } else {
    while(current->get_type() != LEAF){
      current->searchKey(lo_key, 0, &tmp);
      current = tmp;
    }
    //I will need to be able to search a leaf for a key
    current->searchKey(lo_key, &leaf_pos);
    scan->set_pos(leaf_pos);
  }

  scan->set_leaf(current);
  scan->set_endKey(hi_key);

  return scan;

}

Status BtreeBuilder::findStartPosition(BtreeScan* , KeyId) {
  return OK;
}

Status BtreeBuilder::destroyBtree () {
  delete root;
  return OK;
}




