// File Name : bt_builder.cpp
// Date : 03/06/2013
// Team : Amit & Mike


#include "bt_builder.h"


BtreeBuilder::~BtreeBuilder(){
  destroyBtree();
}

Status BtreeBuilder::insertBuilderKey(KeyId) {

//AMIT
Status insertBuilderKey(KeyId KeyValue) {
	//Step 1 : Find the Child Pointer the KeyId needs to be inserted.
	const int type = root->get_type();
	if (type == LEAF) {
		// Traverse this node and insert your value
		Status ret = root->insertKey(KeyValue,root->get_keyCount()) ; // As defined in bt_node.cpp
		if (ret == LEAF_IS_FULL) {
			//Split the Node.
			//splitNode();	
		}	
		
	}
	else {
		BtreeNode *temp
		root->searchKey(KeyValue,0,&temp);
		while(temp->get_type() != LEAF){
			temp->searchKey(KeyValue,0,&temp);
		}
		Status ret = temp->insertKey(KeyValue,temp->get_keyCout());
		if (ret == LEAF_IS_FULL) {
			//Split the Node.
			//splitNode();	
		}	
	}
	
	
	//Step 2 : If the Child Pointer is of type LEAF, then insert it using leaf insertKey() else return error LEAF IS FULL




}

Status BtreeBuilder::deleteBuilderKey(KeyId) {

}

Status BtreeBuilder::splitNode(KeyId, KeyId *&, BtreeNode *, BtreeNode *&, BtreeNode *&) {


}


BtreeScan* BtreeBuilder::openScan(KeyId lo_key, KeyId hi_key) {

}

Status BtreeBuilder::findStartPosition(BtreeScan* , KeyId) {

}

Status BtreeBuilder::destroyBtree () {
  delete root;
  return OK;
}




