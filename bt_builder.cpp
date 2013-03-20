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
	const int type = get_type(root);
	if (type == LEAF) {
		// Traverse this node and insert your value
		root->insertKey(KeyValue,root->get_keyCount()) ; // As defined in bt_node.cpp
		
	}
	else {
			
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




