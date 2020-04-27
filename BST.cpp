#include "BST.h"

bool BST::insertNode(int num) // º¯°æ
{
	// p¸¦ rootºÎÅÍ p¸¦ ³ÖÀ» ÀÚ¸®±îÁö(null¸¸³¯¶§±îÁö) Å¸°í³»·Á°¡±â
	// p¸¦ °»½ÅÇÏ±â Àü q¿¡ p¸¦ ³ÖÀ½ -> q´Â pÀÇ °»½Å Àü ³ëµå
	Node* p = root, * q = 0;
	bool returnValue = false;
	while (p)
	{
		q = p;

		if (num == p->data)
			return returnValue;

		if (num > p->data)
			p = p->rightChild;

		else if (num < p->data)
			p = p->leftChild;
	}

	p = new Node(num); // p´Â ´Ü¸»³ëµå, ÀÚ½Ä¸µÅ©´Â NULL

	// Á¶°Ç¿¡ µû¶ó q¿Í p¸¦ ¿¬°á
	if (!root)
		root = p;

	else if (num > q->data)
		q->rightChild = p;

	else
		q->leftChild = p;

	returnValue = true;
	return returnValue;
}


BST::BST() { // »ý¼ºÀÚ, root¸¦ null·Î ÃÊ±âÈ­
	root = 0;
}

void BST::nodeTraversal() { // driver
	nodeTraversal(root);
}

void BST::nodeTraversal(Node* currentNode) { //workhorse
	if (currentNode) {
		nodeTraversal(currentNode->leftChild);
		cout << currentNode->data << " ";
		nodeTraversal(currentNode->rightChild);
	}
