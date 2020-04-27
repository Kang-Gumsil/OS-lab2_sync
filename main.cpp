//#include <iostream>
//#include <pthread.h>
//#include "CoarseBST.h"
//#include "LockBST.h"
//#include "LocklessBST.h"
//using namespace std;
//
//int main()
//{
//	LocklessBST t;
//	int pthread[4];
//
//	for (int i = 0; i < 4; i++) {
//		if ((pthread_create(&pthread[i]), NULL, 
//	}
//
//	t.insertNode(5); t.insertNode(3); t.insertNode(11); t.insertNode(3); t.insertNode(15);
//	t.insertNode(2); t.insertNode(8); t.insertNode(22); t.insertNode(20); t.insertNode(9);
//
//	t.nodeTraversal();
//	cout << endl << endl;
//
//	cout << "2 탐색 : " << t.search(2) << endl;
//	cout << "30 탐색 : " << t.search(30) << endl << endl;
//
//	cout << "3 삭제 : " << t.deleteNode(3) << endl;
//	cout << "11 삭제 : " << t.deleteNode(11) << endl << endl;
//
//	t.nodeTraversal();
//	cout << endl << endl;
//
//	t.insertNode(3); t.insertNode(17); t.insertNode(22); t.insertNode(7); t.insertNode(12);
//
//	cout << "22 탐색 : " << t.search(22) << endl;
//	cout << "30 탐색 : " << t.search(30) << endl << endl;
//
//	cout << "17 삭제 : " << t.deleteNode(17) << endl;
//	cout << "23 삭제 : " << t.deleteNode(23) << endl << endl;
//
//	t.nodeTraversal();
//	cout << endl << endl;
//}






// 금실 해보기

#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "CoarseBST.h"
//#include "LockBST.h"
#include "LocklessBST.h"
#include <pthread.h>

using namespace std;
LocklessBST t;

typedef struct __mutexArgs {
	int numIteration;
	bool isSync;
} mutexArgs;

static void* testBST(void* arg) {

	mutexArgs *args = (mutexArgs *)arg;
	if (args->isSync == false) { // 락X
		for (int i = 0; i < args->numIteration; i++) {
			t.insertNode(rand() % 1000);
		}
		for (int i = 0; i < args->numIteration; i++) {
			t.deleteNode(rand() % 1000);
		}
	}
}

void mutex_test(int numThreads, int numIteration, bool isSync) {

	// 쓰레드 배열 생성
	pthread_t* pthreads = new pthread_t[numThreads];

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
	t.nodeTraversal();
}


int main() {
	srand((unsigned int)time(NULL));
	mutex_test(4, 1000, false);
}
