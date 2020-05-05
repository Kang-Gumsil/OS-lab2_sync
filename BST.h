/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 32180009, 32181893
*	    Student name : 강금실, 박지은
*
*   BST.cpp :
*       - Lab2 source file for BST.
*
*
*/

#ifndef BST_H
#define BST_H
#include <iostream>
#include "Node.h"

using namespace std;

class BST {
protected:
	Node* root;
	int nodeCount;

public:
	BST();
	Node* search(int num);
	virtual bool insertNode(int num) = 0;
	virtual bool deleteNode(int num) = 0;
	int nodeTraversal();
	void nodeTraversal(Node* currentNode);
};
#endif