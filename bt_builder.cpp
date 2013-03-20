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
		Status ret = root->insertKey(KeyValue,root->get_keyCount()) ; // As defined in bt_node.cpp
		if (ret == LEAF_IS_FULL) {
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
		Status ret = temp->insertKey(KeyValue,temp->get_keyCount());
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

Status BtreeBuilder::splitNode(KeyId KeyValue, KeyId *&, BtreeNode * FullNode, BtreeNode *& lChild, BtreeNode *& rChild) {
		



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




