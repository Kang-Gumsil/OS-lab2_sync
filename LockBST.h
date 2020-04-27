#ifndef LOCK_BST_H
#define LOCK_BST_H
#include <iostream>
#include "Node.h"

using namespace std;

class LockBST : public BST {
public:
	LockBST();
	Node* search(int num);
	bool insertNode(int num);
	bool deleteNode(int num);

};
#endif