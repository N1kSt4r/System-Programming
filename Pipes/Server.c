#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include "message.h"

HANDLE hEventRead, hEventReaded;
HANDLE hReadPipe, hWritePipe, hWritePipeWithoutInheretance;
HANDLE* hReadPipes;
HANDLE* hWritePipes;
HANDLE* hProcesses;
STARTUPINFO* si;
PROCESS_INFORMATION* pi;
char** names;
int numClients;

int WINAPI getMessages() {
	int indexByName;
	while (TRUE) {
		Message mess;
		ReadFile(hReadPipe, &mess, sizeof(mess), NULL, NULL);
		for (indexByName = 0; indexByName < numClients && strcmp(names[indexByName], mess.receiver) != 0; ++indexByName);
		if (indexByName < numClients && strcmp(mess.receiver, mess.sender) != 0) {
			printf("from: %s; to: %s; message: %s\n", mess.sender, mess.receiver, mess.text);
			WriteFile(hWritePipes[indexByName], &mess, sizeof(mess), NULL, NULL);
		}
		else {
			printf("Invalid client\n");
		}
	}
	return 0;
}

int main() {
	SECURITY_ATTRIBUTES attributes;
	attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	attributes.lpSecurityDescriptor = NULL;
	attributes.bInheritHandle = TRUE;

	CreatePipe(&hReadPipe, &hWritePipeWithoutInheretance, NULL, 0);
	DuplicateHandle(
		GetCurrentProcess(), hWritePipeWithoutInheretance,
		GetCurrentProcess(), &hWritePipe,
		0, TRUE, DUPLICATE_SAME_ACCESS
	);
	CloseHandle(hWritePipeWithoutInheretance);

	printf("Enter number of clients and their names: ");
	scanf("%d", &numClients);

	si = calloc(numClients, sizeof(STARTUPINFO));
	pi = calloc(numClients, sizeof(PROCESS_INFORMATION));
	hProcesses = calloc(numClients, sizeof(HANDLE));
	hReadPipes = calloc(numClients, sizeof(HANDLE));
	hWritePipes = calloc(numClients, sizeof(HANDLE));

	HANDLE hThreadGetMessages = CreateThread(NULL, 0, getMessages, NULL, NULL, NULL);

	names = calloc(numClients, sizeof(char*));
	for (int i = 0; i < numClients; ++i) {
		CreatePipe(&hReadPipes[i], &hWritePipes[i], &attributes, 0);

		names[i] = malloc(10);
		scanf("%s", names[i]);
		char request[40];
		sprintf(request, "Client.exe %s %d %d", names[i], hWritePipe, hReadPipes[i]);

		si[i].cb = sizeof(STARTUPINFO);
		CreateProcess(NULL, request, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si[i], &pi[i]);
		hProcesses[i] = pi[i].hProcess;
	}

	WaitForMultipleObjects(numClients, hProcesses, TRUE, INFINITE);
	for (int i = 0; i < numClients; ++i) {
		CloseHandle(pi[i].hThread);
		CloseHandle(pi[i].hProcess);
		CloseHandle(hWritePipes[i]);
		CloseHandle(hReadPipes[i]);
	}
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);

	CloseHandle(hEventRead);
	CloseHandle(hEventReaded);
	CloseHandle(hThreadGetMessages);

	for (int i = 0; i < numClients; ++i) {
		free(names[i]);
	}
	free(names);
	free(si);
	free(pi);
	free(hProcesses);
	return 0;
}