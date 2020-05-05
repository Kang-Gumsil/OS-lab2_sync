/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 32180009, 32181893
*	    Student name : 강금실, 박지은
*
*   FineBST.cpp :
*       - Lab2 source file for Fine-grained lock BST.
*
*
*/

#include "FineBST.h"
#include <pthread.h>

FineBST::FineBST() {
	pthread_mutex_init(&treeLock, NULL);
}

bool FineBST::insertNode(int num) // 삽입
{
	pthread_mutex_lock(&treeLock);	// 트리에 대한 lock

	bool rootAdd = false;
	Node* p = root, * q = 0;
	bool returnValue = true;

	// root가 비어있다면 root에 새로운 노드 추가
	if (root == NULL) {
		p = new Node(num);
		root = p;
		rootAdd = true;
	}

	// root가 비어있지 않다면 root에 대해 lock
	else
		pthread_mutex_lock(&root->nodeLock);

	pthread_mutex_unlock(&treeLock);	// tree에 대한 lock 해제

	// root에 새로운 노드를 추가하지 않았다면 = 처음 들어왔을 때 root가 null이 아니었다면
	if (!rootAdd) {

		// p로 root부터 삽입할 위치(NULL이 나올 때까지) 찾아가기
		// q는 p의 부모 노드, p가 NULL이 되면 종료
		while (p != NULL) {

			q = p;			// q를 p 위치로 이동

			// 삽입하고자 하는 값이 트리 안에 존재한다면 return value에 false 넣고 반복문 종료
			if (num == p->data) {
				returnValue = false;
				break;
			}

			// p로 값 비교하며 삽입 위치 찾기
			if (num > p->data)
				p = p->rightChild;

			else if (num < p->data)
				p = p->leftChild;

			// p가 NULL이 아니라면(아직 삽입 위치에 도달하지 못했다면) 다음 노드로 이동한 p에 대해 lock
			// 이전 p(현재 q)에 대해 lock 해제
			if (p != NULL) {
				pthread_mutex_lock(&p->nodeLock);
				pthread_mutex_unlock(&q->nodeLock);
			}
		}

		// 만약 삽입하고자 하는 값이 트리 안에 존재하지 않았다면
		if (returnValue) {

			p = new Node(num); // p에 새로운 노드 생성

			// 조건에 따라 p와 p의 부모 노드인 q 연결
			if (num > q->data) {
				q->rightChild = p;
			}

			else {
				q->leftChild = p;
			}
		}
		// 삽입 완료 후 새로 삽입된 노드의 부모 노드에 대한 lock 풀어줌
		pthread_mutex_unlock(&q->nodeLock);
	}
	return returnValue;
}
  

bool FineBST::deleteNode(int num) {
	// 삭제할 노드 p 찾고, 만약 없으면 false 리턴
	if (root)
		pthread_mutex_lock(&root->nodeLock);

	Node* p = root, * q = 0;
	bool returnValue = true;

	while (p) {
		if (num == p->data)
			break;

		else {
			if (q) {
				// null 참조 -> 세그먼테이션 오류
				pthread_mutex_unlock(&q->nodeLock);
			}

			q = p;

			if (num > p->data)
				p = p->rightChild;

			else
				p = p->leftChild;

			if (p)
				pthread_mutex_lock(&p->nodeLock);

			else {
				if (q) {
					pthread_mutex_unlock(&q->nodeLock);
				}
			}
		}
	}

	// p, q가 락되어 있는 상태
	if (!p)
		returnValue = false;

	if (returnValue) {
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

			if (q)
				pthread_mutex_unlock(&q->nodeLock);

			// p 언락
			pthread_mutex_unlock(&p->nodeLock);
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

			if (q)
				pthread_mutex_unlock(&q->nodeLock);

			// p 언락
			pthread_mutex_unlock(&p->nodeLock);
		}
		else // 자식이 두개
		{
			if (q)
				pthread_mutex_unlock(&q->nodeLock);
			Node* temp = q = p;
			//q언락
			for (p = p->leftChild; p->rightChild; p = p->rightChild)
				q = p;
			if (q == temp)
				q->leftChild = p->leftChild;
			else
				q->rightChild = p->leftChild;
			temp->data = p->data; //데이터 대체
			pthread_mutex_unlock(&temp->nodeLock);
		}
		
		delete p; // 실제로 삭제할 노드가 삭제된 것이 아니라 대체될 노드가 삭제 
	}
  
	return returnValue;
}
