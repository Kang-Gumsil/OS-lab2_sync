#ifndef BST_H
#define BST_H
#include <iostream>
#include "Node.h"

using namespace std;

class BST {
protected:
	Node* root;

public:
	BST();
	virtual Node* search(int num) = 0;
	virtual Node* searchForDelete(int num) = 0;
	virtual bool insertNode(int num) = 0;
	virtual bool deleteNode(int num) = 0;
	void nodeTraversal();
	void nodeTraversal(Node* currentNode);
};

#endif