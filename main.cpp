//#include <iostream>
//#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "CoarseBST.h"
#include "LockBST.h"
#include "LocklessBST.h"
#include <pthread.h>
using namespace std;

BST* BST_ptr;


typedef struct __mutexArgs {
	int numIteration;
	bool isSync;
} mutexArgs;

static void* insertNode(void* arg) {
	mutexArgs *args = (mutexArgs *)arg;
	for (int i = 0; i < args->numIteration; i++) {
		BST_ptr->insertNode(rand() % 10000);
	}
}

static void* deleteNode(void* arg) {
	mutexArgs* args = (mutexArgs*)arg;
	for (int i = 0; i < args->numIteration; i++) {
		BST_ptr->deleteNode(rand() % 10000);
	}
}

void thread_test() {
	
	enum BSTcat {
		lockless_BST,
		fineGrained_BST,
		CoarseGrained_BST
	};

	for (int i = 0; i < 3; i++) {
		if (i == lockless_BST) {

		}
	}

}

void mutex_test(int numThreads, int numIteration, bool isSync) {

	// 쓰레드 배열 생성
	pthread_t* pthreads = new pthread_t[numThreads];

	// isSync에 따라 객체 생성
	if (isSync == true) BST_ptr = new CoarseBST();
	else BST_ptr = new LocklessBST();
	

	// 인자 생성
	mutexArgs mutex_arg;
	mutex_arg.numIteration = numIteration;
	mutex_arg.isSync = isSync;

	// 쓰레드 수행
	for (int i = 0; i < numThreads; i++) {
		pthread_create(&pthreads[i], NULL, testBST, (void *)&mutex_arg);
	}

	// join
	for (int i = 0; i < numThreads; i++) {
		pthread_join(pthreads[i], NULL);
	}
	BST_ptr->nodeTraversal();
}


int main() {
	srand((unsigned int)time(NULL));
	mutex_test(4, 10000, true);
}