#ifndef COARSE_BST_H
#define COARSE_BST_H
#include <iostream>
#include "Node.h"

using namespace std;

class CoarseBST : public BST {
public:
	CoarseBST();
	Node* search(int num);
	bool insertNode(int num);
	bool deleteNode(int num);

};
#endif