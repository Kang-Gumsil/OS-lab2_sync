#include <iostream>
#include "BST.h"
using namespace std;

int main()
{
	LocklessBST t;

	t.insertNode(5); t.insertNode(3); t.insertNode(11); t.insertNode(3); t.insertNode(15);
	t.insertNode(2); t.insertNode(8); t.insertNode(22); t.insertNode(20); t.insertNode(9);

	t.nodeTraversal();
	cout << endl << endl;

	cout << "2 Å½»ö : " << t.search(2) << endl;
	cout << "30 Å½»ö : " << t.search(30) << endl << endl;

	cout << "3 »èÁ¦ : " << t.deleteNode(3) << endl;
	cout << "11 »èÁ¦ : " << t.deleteNode(11) << endl << endl;

	t.nodeTraversal();
	cout << endl << endl;

	t.insertNode(3); t.insertNode(17); t.insertNode(22); t.insertNode(7); t.insertNode(12);

	cout << "22 Å½»ö : " << t.search(22) << endl;
	cout << "30 Å½»ö : " << t.search(30) << endl << endl;

	cout << "17 »èÁ¦ : " << t.deleteNode(17) << endl;
	cout << "23 »èÁ¦ : " << t.deleteNode(23) << endl << endl;

	t.nodeTraversal();
	cout << endl << endl;
}