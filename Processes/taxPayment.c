#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "taxPayment.h"
#include <stdio.h>

char* toString(taxPayment company) {
	char* a = (char*)malloc(170);
	sprintf(a, "\n%-44s%s\n%-44s%d\n%-44s%.2lf",
		"  �������� ��������: ",				company.name,
		"  ����������������� ����� ��������: ", company.num,
		"  ����� ��������� ��������: ",			company.sum);
	return a;
}