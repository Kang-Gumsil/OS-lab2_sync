/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 32180009, 32181893
*	    Student name : 강금실, 박지은
*
*   LocklessBST.cpp :
*       - Lab2 source file for Lockless BST.
*
*
*/

#ifndef LOCKLESS_BST_H
#define LOCKLESS_BST_H
#include <iostream>
#include "Node.h"
#include "BST.h"

using namespace std;

class LocklessBST : public BST {
public:
	LocklessBST();
	bool insertNode(int num);
	bool deleteNode(int num);

};
#endif