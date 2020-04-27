#include "BST.h"

BST::BST() { // 생성자, root를 null로 초기화
	root = 0;
}

void BST::nodeTraversal() { // driver
	nodeTraversal(root);
}

void BST::nodeTraversal(Node* currentNode) { //workhorse
	if (currentNode)
	{
		nodeTraversal(currentNode->leftChild);
		cout << currentNode->data << " ";
		nodeTraversal(currentNode->rightChild);
	}
}