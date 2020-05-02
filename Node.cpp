#include "Node.h"

Node::Node(int num, Node* left, Node* right)
{
	data = num;
	leftChild = left;
	rightChild = right;
	nodeLock = PTHREAD_MUTEX_INITIALIZER;
//	int rc = pthread_mutex_init(&nodeLock, NULL);
}