#include "SyncQueue.h"
SyncQueue::SyncQueue(int n) {
	maxSize = n + 1;
	start = end = 0;
	storage = new int[maxSize];
	InitializeCriticalSection(&csQueue);
	hSemaphoreNotEmpty = CreateSemaphore(NULL, n, n, NULL);
	hSemaphoreNotFull = CreateSemaphore(NULL, 0, n, NULL);
}
SyncQueue::~SyncQueue() {
	DeleteCriticalSection(&csQueue);
	CloseHandle(hSemaphoreNotEmpty);
	CloseHandle(hSemaphoreNotFull);
	delete[] storage;
}
void SyncQueue::push(int x) {
	WaitForSingleObject(hSemaphoreNotEmpty, INFINITE);
	EnterCriticalSection(&csQueue);
	storage[end++] = x;
	end %= maxSize;
	LeaveCriticalSection(&csQueue);
	ReleaseSemaphore(hSemaphoreNotFull, 1, NULL);
}
int SyncQueue::pop() {
	WaitForSingleObject(hSemaphoreNotFull, INFINITE);
	EnterCriticalSection(&csQueue);
	int temp = storage[start++];
	start %= maxSize;
	LeaveCriticalSection(&csQueue);
	ReleaseSemaphore(hSemaphoreNotEmpty, 1, NULL);
	return temp;
}