﻿#include "CoarseBST.h"
#include <pthread.h>

CoarseBST::CoarseBST() {
	root = 0;
	lock = PTHREAD_MUTEX_INITIALIZER;
//	int rc = pthread_mutex_init(&lock, NULL);
}

Node* CoarseBST::search(int num)
{
	pthread_mutex_lock(&lock);
	// p를 root부터 차례로 내려가면서 탐색
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
	pthread_mutex_unlock(&lock);

	return returnValue; // 원하는 값을 찾았으면 p리턴, p가 null이 될 때까지 못찾으면 탐색 실패, null 리턴
}

Node* CoarseBST::searchForDelete(int num)
{
	// p를 root부터 차례로 내려가면서 탐색
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

	return returnValue; // 원하는 값을 찾았으면 p리턴, p가 null이 될 때까지 못찾으면 탐색 실패, null 리턴
}

bool CoarseBST::insertNode(int num) // 삽입
{
	pthread_mutex_lock(&lock);

	// p를 root부터 p를 넣을 자리까지(null만날때까지) 타고내려가기
	// p를 갱신하기 전 q에 p를 넣음 -> q는 p의 갱신 전 노드
	Node* p = root, * q = 0;
	bool returnValue = true;
	while (p)
	{
		q = p;

		if (num == p->data) {
			returnValue = false;
			break;
		}
			

		if (num > p->data)
			p = p->rightChild;

		else if (num < p->data)
			p = p->leftChild;
	}

	p = new Node(num); // p는 단말노드, 자식링크는 NULL

	if (returnValue) {
		// 조건에 따라 q와 p를 연결
		if (!root) {
			root = p;
		}

		else if (num > q->data) {
			q->rightChild = p;
		}

		else {
			q->leftChild = p;
		}
	}

	pthread_mutex_unlock(&lock);

	return returnValue;
}


bool CoarseBST::deleteNode(int num)
{
	pthread_mutex_lock(&lock);
	// 삭제할 노드 p 찾고, 만약 없으면 false 리턴
	Node* p = searchForDelete(num);
	bool returnValue = false;

	if (p) {
		// p의 부모노드 q 찾기, 만약 q의 자식 중 하나가 p면 찾은것
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

		// p의 자식 수
		int count = 0;
		if (p->leftChild) count++;
		if (p->rightChild) count++;

		if (count == 0) // 단말노드
		{

			// 삭제할 노드를 삭제
			if (p == root)
				root = 0;

			else if (p == q->rightChild)
				q->rightChild = 0;

			else
				q->leftChild = 0;
		}

		else if (count == 1) // 자식이 한개
		{
			// 삭제할 노드를 삭제하고, 그 자리를 자식노드로 채움
			Node* child;

			if (p->rightChild)
				child = p->rightChild;

			else
				child = p->leftChild;

			// 대체한 자식노드와 삭제할 노드의 부모노드와 연결
			if (p == root)
				root = child;

			else if (p == q->rightChild)
				q->rightChild = child;

			else
				q->leftChild = child;

		}

		else // 자식이 두개
		{
			Node* temp = q = p;

			for (p = p->leftChild; p->rightChild; p = p->rightChild)
				q = p;

			if (q == temp)
				q->leftChild = p->leftChild;

			else
				q->rightChild = p->leftChild;

			temp->data = p->data; //데이터 대체
		}

		delete p; // 실제로 삭제할 노드가 삭제된 것이 아니라 대체될 노드가 삭제 
		returnValue = true;
	}

	pthread_mutex_unlock(&lock);

	return returnValue;
}
