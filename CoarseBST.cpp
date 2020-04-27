#include "CoarseBST.h"

CoarseBST::CoarseBST() {
	root = 0;
}

Node* CoarseBST::search(int num)
{
	// p�� root���� ���ʷ� �������鼭 Ž��
	Node* p = root;
	Node* returnValue = 0;
	while (p)
	{
		if (p->data == num) {
			returnValue = p;
			break;
		}

		else if (num > p->data)
			p = p->rightChild;

		else
			p = p->leftChild;
	}

	return returnValue; // ���ϴ� ���� ã������ p����, p�� null�� �� ������ ��ã���� Ž�� ����, null ����
}


bool CoarseBST::deleteNode(int num)
{
	// ������ ��� p ã��, ���� ������ false ����
	Node* p = search(num);
	bool returnValue = false;

	if (p) {
		// p�� �θ��� q ã��, ���� q�� �ڽ� �� �ϳ��� p�� ã����
		Node* q = root;
		if (p != root)
		{
			while (1)
			{
				if (q->leftChild == p || q->rightChild == p)
					break;

				if (num > q->data)
					q = q->rightChild;

				else
					q = q->leftChild;
			}
		}

		// p�� �ڽ� ��
		int count = 0;
		if (p->leftChild) count++;
		if (p->rightChild) count++;

		if (count == 0) // �ܸ����
		{

			// ������ ��带 ����
			if (p == root)
				root = 0;

			else if (p == q->rightChild)
				q->rightChild = 0;

			else
				q->leftChild = 0;
		}

		else if (count == 1) // �ڽ��� �Ѱ�
		{
			// ������ ��带 �����ϰ�, �� �ڸ��� �ڽĳ��� ä��
			Node* child;

			if (p->rightChild)
				child = p->rightChild;

			else
				child = p->leftChild;

			// ��ü�� �ڽĳ��� ������ ����� �θ���� ����
			if (p == root)
				root = child;

			else if (p == q->rightChild)
				q->rightChild = child;

			else
				q->leftChild = child;

		}

		else // �ڽ��� �ΰ�
		{
			Node* temp = q = p;

			for (p = p->leftChild; p->rightChild; p = p->rightChild)
				q = p;

			if (q == temp)
				q->leftChild = p->leftChild;

			else
				q->rightChild = p->leftChild;

			temp->data = p->data; //������ ��ü
		}

		delete p; // ������ ������ ��尡 ������ ���� �ƴ϶� ��ü�� ��尡 ���� 
		returnValue = true;
	}

	return returnValue;
}
