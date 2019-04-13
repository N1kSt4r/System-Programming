#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	bool isOK = true;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	char filename[30];
	printf("Введите имя файла с данными: ");
	scanf("%s", filename);
	int numRecords;
	printf("Введите количество записей:  ");
	scanf("%d", &numRecords);

	char* creatorRequest = (char*)malloc(80);
	sprintf(creatorRequest, "%s \"%s\" %d", "Creator.exe", filename, numRecords);

	isOK = isOK && CreateProcess(NULL, (LPSTR)creatorRequest,
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);

	WaitForSingleObject(piApp.hProcess, INFINITE);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	free(creatorRequest);

	if (isOK) {
		char reportName[30];
		printf("Введите имя файла отчета:    ");
		scanf("%s", reportName);
		double value;
		printf("Введите значение платежей:   ");
		scanf("%lf", &value);
		char operation[2];
		printf("Больше или меньше? (>, <):   ");
		scanf("%s", &operation);

		char* reporterRequest = (char*)malloc(80);
		sprintf(reporterRequest, "%s \"%s\" \"%s\" %.2f \"%s\"",
			"Reporter.exe", filename, reportName, value, operation);
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		isOK = isOK && CreateProcess(NULL, (LPSTR)reporterRequest,
			NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);

		WaitForSingleObject(piApp.hProcess, INFINITE);
		CloseHandle(piApp.hThread);
		CloseHandle(piApp.hProcess);
		free(reporterRequest);

		FILE* reportFile = fopen(reportName, "r");
		if (reportFile) {
			printf("\n");
			while (!feof(reportFile)) {
				char str[80] = {};
				//fscanf(reportFile, "%[^\n]%s", str);
				fgets(str, 78, reportFile);
				printf("%s", str);
			}
			printf("\n");
			printf(isOK ? "Успешное завершение работы. " : "Во время работы произошла ошибка. ");
		}
		else {
			printf("\nНе удалось открыть файл отчета. ");
		}
	}
	else {
		printf("Во время работы произошла ошибка. ");
	}

	system("pause");
	return 0;
}