#ifndef NODE_H 
#define NODE_H
class BST;
class Node {
	friend BST;

private:
	int data;
	Node* leftChild, * rightChild;

public:
	Node(int num, Node* left = 0, Node* right = 0);
};
#endif