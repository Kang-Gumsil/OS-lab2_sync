#include "BST.h"

BST::BST() { // 생성자, root를 null로 초기화
	root = 0;
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

void BST::nodePrint() { // driver
	nodePrint(root);
	cout << endl;
}

void BST::nodePrint(Node* currentNode) { //workhorse
	if (currentNode) {
		nodePrint(currentNode->leftChild);
		cout << currentNode->data << " ";
		nodePrint(currentNode->rightChild);
	}
}
