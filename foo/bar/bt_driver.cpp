// File name: bt_driver.cpp
// Date : 03/06/20130
// Team : Amit & Mike

#include <cmath> 
#include <iostream>
#include <stdio.h>
#include <cstdlib>

#include "bt_builder.h"
#include "bt_node.h"
#include "bt_errors.h"
#include "bt_leaf.h"
#include "bt_index.h"
#include "bt_driver.h"
#include "bt_scan.h"

Status BtreeTest::runTests(){

	test1();
	test2();
	test3();
	test4();

	cout<<"B+tree test complete"<<endl;
	return OK;

}

void BtreeTest::test1() {

	cout << "\n---------test1()  key type is Integer-- initial test------\n";

	Status status;
    	KeyId num = 25;
    	BtreeBuilder *btb = new BtreeBuilder();
	
        status = btb->deleteBuilderKey(num);
	if (status == OK)
	{
		cout<<"Problem with delete function!!!!!"<<endl;
	}else{
		cout<<"Deletion of key ["<<num<<"] failed as expected"<<endl;
	}

	status = btb->destroyBtree();
	if(status != OK)
	{
		cout<<"Problem with BTree destroy!!!!"<<endl;
	}

	delete btb;

	cout << "\n---------------End of Test 1----------------------\n\n";

}


void BtreeTest::test2() {

    	cout << "\n---------test2()  key type is Integer--sequential insertion and deletion test------\n";

    	Status status;
    	KeyId num = 10000;
    	BtreeBuilder *btb = new BtreeBuilder();
    
	//test inserting 10000 keys
	for(int i = 0; i < num;i++)
	{
		status = btb->insertBuilderKey(i);
		if (status == OK){
			cout<<"Inserted key ["<<i<<"] successfully!"<<endl;
		}else{
		
			cout<<"Problem encountered while inserting key ["<<i<<"]"<<endl;
		}
	}

  	// test delete()
    	cout << "\nstart Btree deletion"<< endl;
    	for (int j = 0; j < num; j++) 
	{
		status = btb->deleteBuilderKey(j);
		if (status == OK){
			cout<<"Deleted key ["<<j<<"] successfully!"<<endl;
		}else if(status == KEY_NOT_FOUND){
			cout<<"Key "<<j<<" does not exist in the B+tree"<<endl;
		}else{
			cout<<"Problem encountered while deleting key ["<<j<<"]"<<endl;
		}
	}
	
	status = btb->destroyBtree();
	if(status != OK)
	{
		cout<<"Problem with BTree destroy!!!!"<<endl;
	}

	delete btb;

    cout << "\n---------------End of Test 2----------------------\n\n";
}

void BtreeTest::test3() {

	cout << "\n-------------test3()  key type is Integer-random insertion and deletion-----------\n";

	Status status, status1;
	int num_mult, num_add; 
	int num = 5000;
	int num1, num2;
	BtreeBuilder *btb = new BtreeBuilder();
	num1 = 5;
	num2 = 1;

	//test inserting keys
	for(int i = 0; i < num ;i++)
	{
		num_mult = (num1 * num2);
		status = btb->insertBuilderKey(num_mult);
		if (status == OK){
			cout<<"Inserted key ["<<num_mult<<"] successfully!"<<endl;
		}else{
			cout<<"Problem encountered while inserting key ["<<num_mult<<"]"<<endl;
		}
		
		num_add = (num1 + num2);
		status1 = btb->insertBuilderKey(num_add);
		if (status1 == OK){
			cout<<"Inserted key ["<<num_add<<"] successfully!"<<endl;
		}else{
			cout<<"Problem encountered while inserting key ["<<num_add<<"]"<<endl;
		}
		
		num2++;
	}
	
	//deletion test
	num1 = 5;
	num2 = 1;
	for(int i = 0; i < num ;i++)
	{
		num_mult = (num1 * num2);
		status = btb->deleteBuilderKey(num_mult);
		if (status == OK){
			cout<<"Deleted key ["<<num_mult<<"] successfully!"<<endl;
		}else if(status == KEY_NOT_FOUND){
			cout<<"Key "<<i<<" does not exist in the B+tree"<<endl;
		}else{
			cout<<"Problem encountered while deleting key ["<<num_mult<<"]"<<endl;
		}
		
		num_add = (num1 + num2);
		status1 = btb->deleteBuilderKey(num_add);
		if (status1 == OK){
			cout<<"Deleted key ["<<num_add<<"] successfully!"<<endl;
		}else{
			cout<<"Problem encountered while deleting key ["<<num_add<<"]"<<endl;
		}
		
		num2++;
	}
	
	status = btb->destroyBtree();
	if(status != OK)
	{
		cout<<"Problem with BTree destroy!!!!"<<endl;
	}

	delete btb;

	cout << "\n ----End of Test 3----------------------\n\n";
}

void BtreeTest::test4() {

    	cout << "\n---------test4()  key type is Integer--scan test------\n";


    	Status status;
    	KeyId num = 2000;
    	BtreeBuilder *btb = new BtreeBuilder();
	
	BtreeScan *new_scan;
    	KeyId k, *key;
	key = &k;

	int count = 0;
	
	//test inserting 2000 keys
	for(int i = 0; i < num;i++)
	{
		status = btb->insertBuilderKey(i);
		if (status == OK){
			cout<<"Inserted key ["<<i<<"] successfully!"<<endl;
		}else{
		
			cout<<"Problem encountered while inserting key ["<<i<<"]"<<endl;
		}
	}

	//scan test
	cout<<"whole tree scan"<<endl;

	new_scan = btb->openScan((KeyId)NULL,(KeyId)NULL);
	while((status = new_scan->getNext(key)) ==OK)
	{
		count++;
		cout<<"Scanned key ["<<*key<<"]"<<endl;
	}
	cout<<"Scanned "<<count<<" Keys"<<endl;
	
	cout<<"range tree scan first to 500"<<endl;
	new_scan = btb->openScan((KeyId)NULL,500);
	while((status = new_scan->getNext(key)) ==OK)
	{
		count++;
		cout<<"Scanned key ["<<*key<<"]"<<endl;
	}
	cout<<"Scanned "<<count<<" Keys"<<endl;


	cout<<"range tree scan 500 to 1000"<<endl;
	new_scan = btb->openScan(500,1000);
	while((status = new_scan->getNext(key)) ==OK)
	{
		count++;
		cout<<"Scanned key ["<<*key<<"]"<<endl;
	}
	cout<<"Scanned "<<count<<" Keys"<<endl;


	cout<<"range tree scan 1500 to last"<<endl;
	new_scan = btb->openScan(1500, (KeyId)NULL);
	  while((status = new_scan->getNext(key)) == OK)
	{
		count++;
		cout<<"Scanned key ["<<*key<<"]"<<endl;
	}
	cout<<"Scanned "<<count<<" Keys"<<endl;

    cout << "\n\n---------End of Test 4 ---------------------\n\n";

}

