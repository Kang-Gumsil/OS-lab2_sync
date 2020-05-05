/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 32181893
*	    Student name : 박지은
*
*   CoarseBST.cpp :
*       - Lab2 source file for Coarse-grained lock BST.
*
*
*/

#ifndef COARSE_BST_H
#define COARSE_BST_H
#include <iostream>
#include <pthread.h>
#include "Node.h"
#include "BST.h"

using namespace std;

class CoarseBST : public BST {
private :
	pthread_mutex_t lock;
public:
	CoarseBST();
	bool insertNode(int num);
	bool deleteNode(int num);

};
#endif