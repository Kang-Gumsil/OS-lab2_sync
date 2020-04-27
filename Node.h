#ifndef NODE_H 
#define NODE_H

class BST;
class CoarseBST;
class LockBST;
class LocklessBST;

class Node {
	friend BST;
	friend CoarseBST;
	friend LockBST;
	friend LocklessBST;

private:
	int data;
	Node* leftChild, * rightChild;

public:
	Node(int num, Node* left = 0, Node* right = 0);
};
#endif