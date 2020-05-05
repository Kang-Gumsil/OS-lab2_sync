#ifndef NODE_H 
#define NODE_H

#include <pthread.h>

class BST;
class CoarseBST;
class FineBST;
class LocklessBST;

class Node {
	friend BST;
	friend CoarseBST;
	friend FineBST;
	friend LocklessBST;

private:
	int data;
	Node* leftChild, * rightChild;
	pthread_mutex_t nodeLock;

public:
	Node(int num, Node* left = 0, Node* right = 0);
};
#endif