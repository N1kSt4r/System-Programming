//#define _CRT_SECURE_NO_WARNINGS
//#include <stdlib.h>
//#include <stdio.h>
//#include <windows.h>
//#include "taxPayment.h"
//
//int main(int n, char* args[]) {
//	SetConsoleOutputCP(1251);
//	SetConsoleCP(1251);
//	FILE* file = fopen(args[1], "wb");
//	for (int i = 0, n = atoi(args[2]); i < n; ++i) {
//		taxPayment temp = getCompanyInfo();
//		fwrite(&temp, sizeof(taxPayment), 1, file);
//	}
//	fflush(file);
//	fclose(file);
//	return 0;
//}