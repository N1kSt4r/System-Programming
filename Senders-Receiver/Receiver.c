#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <string.h>


int main() {
	int numSenders;
	char filename[30];
	printf("Enter amount of senders and filename:  ");
	scanf("%d ", &numSenders);
	gets(filename);

	FILE* file = fopen(filename, "wb");
	fclose(file);

	char request[40];
	sprintf(request, "Sender.exe \"%s\"", filename);
	int maxRecords = 2;
	
	HANDLE hMutexFileAccess = CreateMutex(NULL, FALSE, "SenderReader-fileAccess");
	HANDLE hEventReadyToStart = CreateEvent(NULL, TRUE, FALSE, "SenderReader-readyToStart");
	HANDLE hSemaphoreRollCall = CreateSemaphore(NULL, 1, numSenders, "SenderReader-rollcall");
	HANDLE hSemaphoreAllowSending = CreateSemaphore(NULL, maxRecords, maxRecords, "SenderReader-maxRecords");

	STARTUPINFO *si = (STARTUPINFO*)calloc(numSenders, sizeof(STARTUPINFO));
	PROCESS_INFORMATION *piApp = 
		(PROCESS_INFORMATION*)calloc(numSenders, sizeof(PROCESS_INFORMATION));

	for (int i = 0; i < numSenders; ++i) {
		si[i].cb = sizeof(STARTUPINFO);
		CreateProcess(NULL, (LPSTR)request,
			NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[i], &piApp[i]);
	}
	
	WaitForSingleObject(hEventReadyToStart, INFINITE);
	CloseHandle(hSemaphoreRollCall);
	CloseHandle(hEventReadyToStart);

	int working = numSenders;
	while (TRUE) {
		char message[20];
		scanf("%s", message);
		WaitForSingleObject(hMutexFileAccess, INFINITE);

		if (strcmp(message, "read") == 0) {
			file = fopen(filename, "rb");
			int counter = 0;
			while (fread(message, 20, 1, file)) {
				printf("%s\n", message);
				++counter;
			}
			fclose(file);

			file = fopen(filename, "wb");
			fclose(file);

			ReleaseSemaphore(hSemaphoreAllowSending, counter, NULL);
			
			ReleaseMutex(hMutexFileAccess);
		}
		else {
			CloseHandle(hMutexFileAccess);
			CloseHandle(hSemaphoreAllowSending);
			for (int i = 0; i < numSenders; ++i) {
				CloseHandle(piApp[i].hThread);
				CloseHandle(piApp[i].hProcess);
			}
			return 0;
		}
	}

	return 0;
}