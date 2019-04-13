#include <iostream>
#include "SyncQueue.h"

using namespace std;

SyncQueue* queue;
CRITICAL_SECTION csInOut;
HANDLE hEventReadyToStart;
HANDLE hSemaphoreRollCall;

DWORD WINAPI producer(LPVOID param) {
	if (!ReleaseSemaphore(hSemaphoreRollCall, 1, NULL)) {
		wcout << "Consumers and producers are ready\n";
		SetEvent(hEventReadyToStart);
	}
	WaitForSingleObject(hEventReadyToStart, INFINITE);
	EnterCriticalSection(&csInOut);
	int n, t;
	wcout << "Enter amount and type of produced products: ";
	wcin >> n >> t;
	LeaveCriticalSection(&csInOut);
	for (int i = 0; i < n; ++i) {
		Sleep(15);
		queue->push(t);
		EnterCriticalSection(&csInOut);
		wcout << "Product " << t << " produced" << endl;
		LeaveCriticalSection(&csInOut);
	}
	return 0;
}
DWORD WINAPI consumer(LPVOID param) {
	if (!ReleaseSemaphore(hSemaphoreRollCall, 1, NULL)) {
		wcout << "Consumers and producers are ready\n";
		SetEvent(hEventReadyToStart);
	}
	WaitForSingleObject(hEventReadyToStart, INFINITE);
	EnterCriticalSection(&csInOut);
	int n, t;
	wcout << "Enter amount of consumed products: ";
	wcin >> n;
	LeaveCriticalSection(&csInOut);
	for (int i = 0; i < n; ++i) {
		Sleep(15);
		t = queue->pop();
		EnterCriticalSection(&csInOut);
		wcout << "\tProduct " << t << " consumed" << endl;
		LeaveCriticalSection(&csInOut);
	}
	return 0;
}

int main() {
	int n, p, c;
	wcout << "Enter size of queue, amount of producers and consumers: ";
	wcin >> n >> p >> c;
	queue = new SyncQueue(n);

	InitializeCriticalSection(&csInOut);
	hSemaphoreRollCall = CreateSemaphore(NULL, 1, p + c, NULL);
	hEventReadyToStart = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE* producers = new HANDLE[p];
	for (int i = 0; i < p; ++i) {
		producers[i] = CreateThread(NULL, 0, producer, NULL, 0, NULL);
	}
	HANDLE* consumers = new HANDLE[c];
	for (int i = 0; i < c; ++i) {
		consumers[i] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
	}

	WaitForMultipleObjects(p, producers, true, INFINITE);
	WaitForMultipleObjects(c, consumers, true, INFINITE);
	for (int i = 0; i < p; ++i) {
		CloseHandle(producers[i]);
	}
	for (int i = 0; i < c; ++i) {
		CloseHandle(consumers[i]);
	}
	DeleteCriticalSection(&csInOut);
	delete[] producers;
	delete[] consumers;
	system("pause");
	return 0;
}