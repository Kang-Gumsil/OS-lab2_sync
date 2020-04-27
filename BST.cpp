#include "BST.h"

BST::BST() { // ������, root�� null�� �ʱ�ȭ
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