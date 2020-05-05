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