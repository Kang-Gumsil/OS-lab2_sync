﻿#ifndef COARSE_BST_H
#define COARSE_BST_H
#include <iostream>
#include "Node.h"
#include "BST.h"

using namespace std;

class CoarseBST : public BST {
public:
	CoarseBST();
	Node* search(int num);
	Node* searchForDelete(int num);
	bool insertNode(int num);
	bool deleteNode(int num);

};
#endif