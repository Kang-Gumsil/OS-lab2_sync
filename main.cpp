#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "CoarseBST.h"
#include "LockBST.h"
#include "LocklessBST.h"
using namespace std;

// type을 쉽게 정의하기 위한 열거형 
enum type {
	coarse_grained = 0,
	fine_grained,
	lockless
};

// 쓰레드의 함수 인자로 사용될 구조체
typedef struct __threadArgs {
	pthread_t thread;
	BST* tree;
	int* dataArr;
	int start, end;
} threadArgs;

double getTimeVal(struct timeval* tv, struct timeval* tv_end);
void printResult(BST* bst, int numThreads, int numIter, int type, double time);
void bstTest(int numThreads, int numIter);
static void* threadNodeInsert(void* tArg);
static void* threadNodeDelete(void* tArg);

int main(int argc, char* argv[]) {

	// 시드 설정
	srand((unsigned int)time(NULL));

	char op;
	int numThreads = 0, numIter = 0;
	while ((op = getopt(argc, argv, "t:c:")) != -1) {
		switch (op) {
		case 't':
			numThreads = atoi(optarg);
			break;
		case 'c':
			numIter = atoi(optarg);
			break;
		default:
			goto INVALID_ARGS;
		}
	}
	if ((numThreads > 0) && (numIter > 0)) {
		bstTest(numThreads, numIter);
	}
	else 
		goto INVALID_ARGS;
	return 0;
	// 잘못된 main 인자의 경우 오류메시지 출력 후 프로그램 종료
	INVALID_ARGS:
		cout << "invalid arguments!" << endl;
		cout << "usage : ./lab2_bst -t 4 -c 1000000" << endl;
		return -1;
}

// 수행된 시간을 구해주는 함수
double getTimeVal(struct timeval* tv, struct timeval* tv_end) {
	double tv_s = tv->tv_sec + (tv->tv_usec / 1000000.0);
	double tv_e = tv_end->tv_sec + (tv_end->tv_usec / 1000000.0);
	return (tv_e - tv_s);
}

// 결과 출력 함수
void printResult(BST* bst, int numThreads, int numIter, int type, double time, string insORdel) {
	string typeArr[] = { "Multi Thread Coarse-grained", "Multi Thread Fine-grained", "Multi Thread Lockless","Single Thread (Lockless)" };
	cout << "=====  " << typeArr[type] << insORdel<< " experiment  =====" << endl;
	cout << " Experiment info " << endl;
	cout << "    test node           : " << numIter << endl;
	cout << "    test threads        : " << numThreads << endl;
	cout << "    execution time      : " << time << " seconds" << endl;
	// 노드 개수 출력?
	//printf("\n BST inorder iteration result : \n");
	//result_count = lab2_node_print_inorder(tree);
	//printf("    total node count    : %d \n\n", node_count);
}

void bstTest(int numThreads, int numIter) {
	BST* bstPtr;
	int iter_temp = numIter / numThreads;
	struct timeval startTime, endTime;
	threadArgs* threads = new threadArgs[numThreads];
	// 테스트 데이터 생성
	// 데이터의 숫자가 적당히 겹치도록 0 ~ numIter-1 까지의 숫자로 지정
	int* data = new int[numIter];
	for (int i = 0; i < numIter; i++) {
		data[i] = rand() % numIter;
	}

	// INSERT
	// 싱글 스레드의 경우 Lockless만 수행하도록..
	if (numThreads == 1) {
		// 객체 생성
		bstPtr = new LocklessBST();
		// 노드 넣기 수행
		gettimeofday(&startTime, NULL);
		for (int k = 0; k < numIter; k++)
			bstPtr->insertNode(data[k]);
		gettimeofday(&endTime, NULL);
		// 결과 출력 및 객체 해제
		printResult(bstPtr, numThreads, numIter, 3, getTimeVal(&startTime, &endTime), " insert");
		delete(bstPtr);
	}
	// 멀티 스레드의 경우 Lockless, Coarse-grained, Fine-grained에 대해 수행
	else {
		for (int i = 1; i < 2; i++) {
			// i값에 따라 객체 생성
			if (i == 0)		  bstPtr = new CoarseBST();
			else if (i == 1)  bstPtr = new LockBST();
			else			  bstPtr = new LocklessBST();

			// 노드 삽입 수행
			gettimeofday(&startTime, NULL);
			for (int k = 0; k < numThreads; k++) {

				// 각 쓰레드에 대한 인자 생성
				threadArgs* tArgs = &threads[k];
				tArgs->tree = bstPtr;
				tArgs->dataArr = data;
				tArgs->start = k * iter_temp;
				tArgs->end = (k + 1) * iter_temp - 1;

				// 쓰레드 생성 및 노드 넣기
				pthread_create(&threads[k].thread, NULL, threadNodeInsert, (void*)tArgs);
			}

			// 쓰레드가 다 수행될 때까지 기다림..
			for (int k = 0; k < numThreads; k++)
				pthread_join(threads[k].thread, NULL);

			gettimeofday(&endTime, NULL);

			// 결과 출력 및 객체 해제
			printResult(bstPtr, numThreads, numIter, i, getTimeVal(&startTime, &endTime), " insert");
			delete(bstPtr);
		}
	}


	// DELETE
	// 싱글 스레드의 경우 Lockless만 수행하도록..
	if (numThreads == 1) {

		// 객체 생성 및 노드 넣기
		bstPtr = new LocklessBST();
		for (int k = 0; k < numIter; k++)
			bstPtr->insertNode(data[k]);

		// 노드 삭제 수행
		gettimeofday(&startTime, NULL);
		for (int k = 0; k < numIter; k++)
			bstPtr->deleteNode(data[k]);
		gettimeofday(&endTime, NULL);

		// 결과 출력 및 객체 해제
		printResult(bstPtr, numThreads, numIter, 3, getTimeVal(&startTime, &endTime), " delete");
		delete(bstPtr);
	}

	// 멀티 스레드의 경우 Lockless, Coarse-grained, Fine-grained에 대해 수행
	else {
		for (int i = 0; i < 1; i++) {

			// i값에 따라 객체 생성 및 노드 삽입 수행
			if (i == 0)		  bstPtr = new CoarseBST();
			else if (i == 1)  bstPtr = new LockBST();
			else			  bstPtr = new LocklessBST();

			for (int k = 0; k < numIter; k++)
				bstPtr->insertNode(data[k]);

			// 노드 삭제 수행
			gettimeofday(&startTime, NULL);
			for (int k = 0; k < numThreads; k++) {
				// 각 쓰레드에 대한 인자 생성
				threadArgs* tArgs = &threads[k];
				tArgs->tree = bstPtr;
				tArgs->dataArr = data;
				tArgs->start = k * iter_temp;
				tArgs->end = (k + 1) * iter_temp - 1;
				// 쓰레드 생성 및 노드 넣기
				pthread_create(&threads[k].thread, NULL, threadNodeDelete, (void*)tArgs);
			}

			// 쓰레드가 다 수행될 때까지 기다림..
			for (int k = 0; k < numThreads; k++)
				pthread_join(threads[k].thread, NULL);

			gettimeofday(&endTime, NULL);

			// 결과 출력 및 객체 해제
			printResult(bstPtr, numThreads, numIter, i, getTimeVal(&startTime, &endTime), " Delete");
			delete(bstPtr);
		}
	}
}

// 트리에 노드 삽입하는 함수
static void* threadNodeInsert(void* tArg) {
	threadArgs *args = (threadArgs*)tArg;
	BST* tree = args->tree;
	int* dataArr = args->dataArr;
	int start = args->start, end = args->end;
	for (int i = start; i < end; i++) 
		tree->insertNode(dataArr[i]);
}

// 트리에 노드 삭제하는 함수
static void* threadNodeDelete(void* tArg) {
	threadArgs* args = (threadArgs*)tArg;
	BST* tree = args->tree;
	int* dataArr = args->dataArr;
	int start = args->start, end = args->end;
	for (int i = start; i < end; i++)
		tree->deleteNode(dataArr[i]);
}
