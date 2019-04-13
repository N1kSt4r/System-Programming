#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "taxPayment.h"
#include <stdio.h>

char* toString(taxPayment company) {
	char* a = (char*)malloc(170);
	sprintf(a, "\n%-44s%s\n%-44s%d\n%-44s%.2lf",
		"  Название компании: ",				company.name,
		"  Идентификационный номер компании: ", company.num,
		"  Сумма налоговых платежей: ",			company.sum);
	return a;
}