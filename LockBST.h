#ifndef LOCK_BST_H
#define LOCK_BST_H
#include <iostream>
#include <pthread.h>
#include "Node.h"
#include "BST.h"

using namespace std;

class LockBST : public BST {
private:
	pthread_mutex_t treeLock;
public:
	LockBST();
	Node* search(int num);
	Node* searchForDelete(int num);
	bool insertNode(int num);
	bool deleteNode(int num);

};
#endif