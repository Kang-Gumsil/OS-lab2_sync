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

#include "Node.h"

Node::Node(int num, Node* left, Node* right)
{
	data = num;
	leftChild = left;
	rightChild = right;
	pthread_mutex_init(&nodeLock, NULL);
}