//#define _CRT_SECURE_NO_WARNINGS
//#include <windows.h>
//#include <stdio.h>
//#include "taxPayment.h"
//
////"file.bin" "output.txt" 4 "<"
//
//int cmp(void* l, void* r) {
//	double lValue = ((taxPayment*)l)->sum;
//	double rValue = ((taxPayment*)r)->sum;
//	if (lValue - rValue < 0) {
//		return 1;
//	}
//	if (lValue - rValue > 0) {
//		return -1;
//	}
//	return 0;
//}
//
//int main(int n, char* args[]) {
//	SetConsoleOutputCP(1251);
//	SetConsoleCP(1251);
//
//	FILE* file = fopen(args[1], "rb");
//	fseek(file, 0, SEEK_END);
//	int num = 0;
//	taxPayment* companies = (taxPayment*)malloc(ftell(file));
//	fseek(file, 0, SEEK_SET);
//
//	taxPayment company;
//	double value = atof(args[3]);
//
//	while (fread(&company, sizeof(taxPayment), 1, file)) {
//		if (args[4][0] == '<') {
//			if (company.sum - value < 0) {
//				companies[num++] = company;
//			}
//		} else {
//			if (company.sum - value > 0) {
//				companies[num++] = company;
//			}
//		}
//	}
//	qsort(companies, num, sizeof(taxPayment), cmp);
//
//	FILE* out = fopen(args[2], "w");
//	fprintf(out, "Отчет по файлу \"%s\"\n", args[1]);
//	fprintf(out, " Список компаний, налоговые платежи которых %s %s:\n", args[4], args[3]);
//	for (int i = 0; i < num; ++i) {
//		char* str = toString(companies[i]);
//		fprintf(out, "%s\n", str);
//		free(str);
//	}
//	fflush(out);
//	fclose(out);
//
//	free(companies);
//	fclose(file);
//	return 0;
//}