#pragma once
#include <windows.h>
class SyncQueue {
	int* storage;
	int maxSize, start, end;
	CRITICAL_SECTION csQueue;
	HANDLE hSemaphoreNotEmpty;
	HANDLE hSemaphoreNotFull;
public:
	SyncQueue(int n);
	~SyncQueue();
	void push(int x);
	int pop();
};