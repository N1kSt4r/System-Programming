#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "taxPayment.h"
#include <stdio.h>

taxPayment getCompanyInfo() {
	taxPayment company;
	printf("\n");
	printf("  Введите название компании:                ");
	scanf("%s", &company.name);
	printf("  Введите идентификационный номер компании: ");
	scanf_s("%d", &company.num);
	printf("  Введите сумму налоговых платежей:         ");
	scanf_s("%lf", &company.sum);
	return company;
}