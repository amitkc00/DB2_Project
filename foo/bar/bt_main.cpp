// File name : bt_main.cpp
// Date : 03/06/2013
// Team : Amit & Mike

#ifndef BT_MAIN_CPP
#define BT_MAIN_CPP

#include "bt_node.h"
#include "bt_leaf.h"
#include "bt_index.h"
#include "bt_builder.h"
#include "bt_driver.h"
#include<cmath>
#include<iostream>
#include <cstdlib>
using namespace std;

int main()
{
  BtreeTest *btt = new BtreeTest();
   Status dbstatus;

   dbstatus = btt->runTests();

   if (dbstatus != OK) {       
      cout << "Error encountered during btree tests: " << endl;     
      return(1);
   }
   
   return(0);
}

#endif
