#pragma once

struct taxPayment {
	int num;		// ����������������� ����� ��������
	char name[10];	// �������� ��������
	double sum;		// ����� ��������� ��������
};

typedef struct taxPayment taxPayment;

taxPayment getCompanyInfo();
char* toString(taxPayment);