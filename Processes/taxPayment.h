#pragma once

struct taxPayment {
	int num;		// идентификационный номер компании
	char name[10];	// название компании
	double sum;		// сумма налоговых платежей
};

typedef struct taxPayment taxPayment;

taxPayment getCompanyInfo();
char* toString(taxPayment);