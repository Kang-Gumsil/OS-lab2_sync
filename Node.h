/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 32180009, 32181893
*	    Student name : 강금실, 박지은
*
*   Node.cpp :
*       - Lab2 source file for Node.
*
*
*/

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