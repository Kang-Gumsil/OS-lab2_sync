#ifndef BST_H
#define BST_H
#include <iostream>
#include "Node.h"

using namespace std;

class BST {
private:
	Node* root;

public:
	BST();
	Node* search(int num);
	bool insertNode(int num);
	bool deleteNode(int num);
	void nodeTraversal();
	void nodeTraversal(Node* currentNode);
};

#endif