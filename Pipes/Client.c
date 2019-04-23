#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include "message.h"


int WINAPI sendMessages(char* args[]) {
	HANDLE hWritePipe;
	sscanf(args[2], "%d", &hWritePipe);

	Message mess;
	sprintf(mess.sender, "%s", args[1]);

	HANDLE hMutexWriteAccess = CreateMutex(NULL, FALSE, "pipesMutexWrite");
	while (TRUE) {
		scanf("%s < %[^\n]s\r", &mess.receiver, &mess.text);
		if (strcmp(mess.receiver, "close") == 0) break;

		WaitForSingleObject(hMutexWriteAccess, INFINITE);
		WriteFile(hWritePipe, &mess, sizeof(mess), NULL, NULL);
		ReleaseMutex(hMutexWriteAccess);
	}
	CloseHandle(hWritePipe);
	return 0;
}

int WINAPI getMessages(char* args[]) {
	HANDLE hReadPipe;
	sscanf(args[3], "%d", &hReadPipe);

	Message mess;
	while (TRUE) {
		ReadFile(hReadPipe, &mess, sizeof(mess), NULL, NULL);
		printf("\r                                                                                     \r");
		printf("%s > %s\n", mess.sender, mess.text);
	}
	return 0;
}

int main(int n, char* args[]) {

	HANDLE hThreadSendMessages = CreateThread(NULL, 0, sendMessages, args, NULL, NULL);
	HANDLE hThreadGetMessages = CreateThread(NULL, 0, getMessages, args, NULL, NULL);

	WaitForSingleObject(hThreadSendMessages, INFINITE);
	CloseHandle(hThreadSendMessages);
	CloseHandle(hThreadGetMessages);
	return 0;
}