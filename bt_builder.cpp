// File Name : bt_builder.cpp
// Date : 03/06/2013
// Team : Amit & Mike


#include "bt_builder.h"

BtreeBuilder::~BtreeBuilder(){
  destroyBtree();
}

Status BtreeBuilder::insertBuilderKey(KeyId) {


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




