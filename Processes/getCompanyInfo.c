#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "taxPayment.h"
#include <stdio.h>

taxPayment getCompanyInfo() {
	taxPayment company;
	printf("\n");
	printf("  ������� �������� ��������:                ");
	scanf("%s", &company.name);
	printf("  ������� ����������������� ����� ��������: ");
	scanf_s("%d", &company.num);
	printf("  ������� ����� ��������� ��������:         ");
	scanf_s("%lf", &company.sum);
	return company;
}