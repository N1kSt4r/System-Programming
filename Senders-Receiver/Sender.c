#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int n, char** args) {
	HANDLE hMutexFileAccess = CreateMutex(NULL, FALSE, "SenderReader-fileAccess");
	HANDLE hEventReadyToStart = CreateEvent(NULL, TRUE, FALSE, "SenderReader-readyToStart");
	HANDLE hSemaphoreRollCall = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SenderReader-rollcall");
	HANDLE hSemaphoreAllowSending = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SenderReader-maxRecords");

	if (!ReleaseSemaphore(hSemaphoreRollCall, 1, NULL)) {
		SetEvent(hEventReadyToStart);
	}
	WaitForSingleObject(hEventReadyToStart, INFINITE);

	while (TRUE) {
		char message[20];
		scanf("%s", message);
		WaitForSingleObject(hSemaphoreAllowSending, INFINITE);
		Sleep(15);
		
		if (strcmp(message, "write") == 0) {
			scanf(" ");
			gets(message);
			WaitForSingleObject(hMutexFileAccess, INFINITE);
			FILE* file = fopen(args[1], "r+b");			

			fseek(file, 0, SEEK_END);
			fwrite(message, sizeof(message), 1, file);

			fflush(file);
			fclose(file);
			ReleaseMutex(hMutexFileAccess);
		} else {
			return 0;
		}
	}
}