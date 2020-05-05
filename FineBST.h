#ifndef FINE_BST_H
#define FINE_BST_H
#include <iostream>
#include <pthread.h>
#include "Node.h"
#include "BST.h"

using namespace std;

class FineBST : public BST {
private:
	pthread_mutex_t treeLock;
public:
	FineBST();
	bool insertNode(int num);
	bool deleteNode(int num);

};
#endif