#include <Windows.h>
#include <stdio.h>
#include "polynom.h"

#define num 2

DWORD WINAPI Polynom(LPVOID param) {
	Sleep(150);
	calculate(param);
	Sleep(150);
	return 0;
}

int main() {
	SetConsoleOutputCP(1251);
	HANDLE hThreads[num];
	Polynomial* polynom[num];

	for (int i = 0; i < num; ++i) {
		polynom[i] = getPolynom();
	}

	int x;
	printf("Enter õ: ");
	scanf_s("%d", &x);

	for (int i = 0; i < num; ++i) {
		setX(polynom[i], x);
		hThreads[i] = CreateThread(NULL, 0, Polynom, polynom[i], 0, NULL);
		if (hThreads[i] == NULL) {
			return GetLastError();
		}
	}

	WaitForMultipleObjects(num, hThreads, TRUE, INFINITE);

	if (valueOf(polynom[1]) != 0) {
		printf("f(%d) = %.4f\n", x, (float)valueOf(polynom[0]) / valueOf(polynom[1]));
	} else {
		printf("Division by zero\n");
	}

	for (int i = 0; i < num; ++i) {
		CloseHandle(hThreads[i]);
		freePolynom(&polynom[i]);
	}
	system("pause");
	return 0;
}

//input
//2 1 2 3
//1 4 7
//
//-10 -> -2.5
//-8  -> -2
// 0  ->  0.4
// 6  ->  1.6