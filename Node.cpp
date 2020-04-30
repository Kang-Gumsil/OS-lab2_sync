#include "Node.h"

Node::Node(int num, Node* left, Node* right)
{
	data = num;
	leftChild = left;
	rightChild = right;
	int rc = pthread_mutex_init(&nodeLock, NULL);
}