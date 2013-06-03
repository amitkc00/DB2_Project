// File name : bt_errors.h
// Date : 03/06/2013
// Team : Amit & Mike

#ifndef BT_ERRORS_H
#define BT_ERRORS_H

const int INDEX = 1;
const int LEAF = 2;

//typedef int NodeId;
typedef int KeyId;


//4 bytes of type,keyCount and parentPtr
//4bytes for zeroth pointer
//4 bytes of key and pointer
const int MAX_NUM_KEYS = (1024 - ((3 * sizeof(int)) + sizeof(int)) ) / (2 * sizeof(int));
 
//In each node number of pointers will be one more than number of keys
const int MAX_NUM_PTRS = (MAX_NUM_KEYS + 1);

//enum for Status
enum Status {
	
	OK,
	DONE,
	NO_MORE_KEYS,
	KEY_NOT_FOUND,
	FAIL,
	
	INVALID_PAGE,
	
	LEAF_IS_FULL,
	LEAF_IS_EMPTY,
	LAST_LEAF_KEY,
	LEAF_HALF_FULL,
	
	INDEX_IS_FULL,
	INDEX_IS_EMPTY,

	NUM_STATUS_CODES
};

#endif

