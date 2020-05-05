/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 32180009, 32181893
*	    Student name : 강금실, 박지은
*
*   BST.cpp :
*       - Lab2 source file for BST.
*
*   
*/

#include "BST.h"

BST::BST() { // 생성자, root를 null로 초기화
	root = 0;
}

Node* BST::search(int num) {

	// p를 root부터 차례로 내려가면서 탐색
	Node* p = root;
	while (p)
	{
		if (p->data == num) // 원하는 값을 찾았으면 p리턴
			return p;

		else if (num > p->data)
			p = p->rightChild;

		else
			p = p->leftChild;
	}

	return 0; // p가 null이 될 때까지 못찾으면 탐색 실패, null 리턴
}


int BST::nodeTraversal() { // driver
	nodeCount = 0;
	nodeTraversal(root);
	return nodeCount;
}

void BST::nodeTraversal(Node* currentNode) { //workhorse
	if (currentNode) {
		nodeTraversal(currentNode->leftChild);
		nodeCount++;
		nodeTraversal(currentNode->rightChild);
	}
}