// File Name : bt_builder.cpp
// Date : 03/06/2013
// Team : Amit & Mike


#include "bt_builder.h"


BtreeBuilder::~BtreeBuilder(){
  destroyBtree();
}


Status BtreeBuilder::insertBuilderKey(KeyId KeyValue) {
	//Step 1 : Find the Child Pointer the KeyId needs to be inserted.
	const int type = root->get_type();
	if (type == LEAF) {
		// Traverse this node and insert your value
		Status ret = root->insertKey(KeyValue,0) ; // As defined in bt_node.cpp
		if (ret == LEAF_IS_FULL) {
			splitNode(KeyValue,,root,getPtr(MAX_NUM_KEYS-1),getPtr(MAX_NUM_KEYS));
			//Split the Node.
			//splitNode();	
		}	
		return OK;	
	}
	else {
	        BtreeNode *temp;
		root->searchKey(KeyValue,0,&temp);
		while(temp->get_type() != LEAF){
			temp->searchKey(KeyValue,0,&temp);
		}

		Status ret = temp->insertKey(KeyValue,0);
		if (ret == LEAF_IS_FULL) {
			//Split the Node.
			//splitNode();	
		}	
		return OK;
	}
	return FAIL; 

}

Status BtreeBuilder::deleteBuilderKey(KeyId) {

}

Status BtreeBuilder::splitNode(KeyId KeyValue, KeyId *&, BtreeNode * FullNode_Ptr, BtreeNode *& lChild_Ptr, BtreeNode *& rChild_Ptr) {
	if (FullNode_Ptr->get_type() == LEAF) {
		BtreeNode New_SplitNode;
		for (int i = MAX_NUM_KEYS/2 ; i < MAX_NUM_KEYS ; i++) {
			Status ret = New_SplitNode->insertKey(FullNode_Ptr->getKey(i),0);
			if(ret != OK)
				return FAIL;
			FullNode_Ptr->setKey(-1,i);
			FullNode_Ptr->set_keyCount(FullNode_Ptr->get_keyCount()-1);
		}
		Status ret2 = New_SplitNode->insertKey(KeyValue,0);
		if(ret2 != OK)
			return FAIL;
		if (FulNode_Ptr == root) {
			BtreeNode New_IndexNode;
			Status ret = New_IndexNode->insertKey(New_SplitNode->getKey(0), int count, FullNode_Ptr, New_SplitNode);
			if (ret == OK)
				root = New_IndexNode;
			else
				return FAIL;
		}
		else { // When it is not root, we need to insert entry for new leaf node in parent node.
			Status ret = (FullNode_ptr->get_parentPtr())->insertKey(NewSplitNode->getKey(0),int count, FullNode_Ptr, New_SplitNode);
			if (return == OK)
				return OK;
			else if (ret == INDEX_IS_FULL) {  // This is a recursive call to splitNode to handle this case.
				ret = splitNode(New_SplitNode->getKey(0),,FullNode_ptr->get_parentPtr(),FullNode_Ptr, New_SplitNode)
				if (return != OK)
					return FAIL;
			}
			else
				return FAIL;
		}
		return OK;
	}
	else if (FullNode_Ptr->get_type() == INDEX) {
		BtreeNode New_IndexNode;
		BtreeNode* FullNode_Ptr_last = FullNode_Ptr->getPtr(MAX_NUM_KEYS-1);
		for (int i = MAX_NUM_KEYS/2 ; i < MAX_NUM_KEYS ; i++) {
			Status ret = New_IndexNode->insertKey(FullNode_Ptr->getKey(i), int count, FullNode_Ptr->getPtr(i), FullNode_Ptr->getPtr(i+1));
			if(ret != OK)
				return FAIL;
			FullNode_Ptr->setKey(-1,i);
			FullNode_Ptr->setPtr(NULL,i);
			FullNode_Ptr->setPtr(NULL,i+1);
            FullNode_Ptr->set_keyCount(FullNode_Ptr->get_keyCount()-1);
		}
		ret = New_IndexNode->insertKey(KeyValue,int count, FullNode_Ptr_last, New_IndexNode);
		if (ret != OK)
			return FAIL;
		if (FullNode_Ptr == root) { //If Full Index Node was root, we create a new Index node and mark it as root after moving our first pointer fron New_IndexNode to it.
			BtreeNode New_IndexNode_root;
			Status ret = New_IndexNode_root->insertKey(New_IndexNode->getKey(0), int count, FullNode_Ptr, New_IndexNode);
			
		}
		else {

		}
		
		//Creat a New Root Node because of Index Node Split and Take the first element from New_IndexNode and move it to Parent Nod.

/*
Step 1 : If 

*/



/*
		if(ret != OK)
			return FAIL;
		

		Status ret = (FullNode_ptr->get_parentPtr())->insertKey(NewSplitNode->getKey(0),int count, FullNode_Ptr, New_SplitNode);
		if (ret == OK)
			return OK;
		else if (ret == FAIL)
			return FAIL;
		else if (return == INDEX_IS_FULL)
			splitNode(KeyValue,,FullNode_Ptr->get_parentPtr(),FullNode_Ptr->getPtr(),FUllNode_Ptr->getPtr());

		if (FulNode_Ptr == root) {
			BtreeNode New_IndexNode;
			Status ret = New_IndexNode->insertKey(New_SplitNode->getKey(0), int count, FullNode_Ptr, New_SplitNode);
			if (ret == OK)
				root = New_IndexNode;
		}
*/
	}
}		



/*
Points for splitNode.

Node *N;
keyId Key;

BtreeNode temp = new LeafNode;

for (i = max-keys/2 ; i < max-keys; i++) {
	temp.setKey(N->getKey(i),i)
	N->setKey(-1,i);
	
}

temp.Set_keyCount(max-keys/2);
N->set_keyCount(max-keys-temp.get_KeyCount());
N->get_ParentPtr()->insertKey(N,temp, temp.getKey(),0)
N->get_ParentPtr()->SearchKey();

*/

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

}

Status BtreeBuilder::destroyBtree () {
  delete root;
  return OK;
}




