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