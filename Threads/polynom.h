#pragma once

struct Polynomial {
	int deg;
	int *coef;
	int *value;
	int x;
};

typedef struct Polynomial Polynomial;

void freePolynom(Polynomial** polynom);
void calculate(Polynomial* polynom);
int valueOf(Polynomial* polynom);
void setX(Polynomial* polynom, int x);
Polynomial* getPolynom();