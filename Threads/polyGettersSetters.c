#include "polynom.h"
#include <stdio.h>

Polynomial* getPolynom() {
	Polynomial* polynom = (Polynomial*)malloc(sizeof(Polynomial));
	polynom->value = 0;
	polynom->x = 0;

	printf("Enter the polynomial degree:       ");
	scanf_s("%d", &polynom->deg);

	polynom->coef = (int*)malloc((polynom->deg + 1) * sizeof(int));
	printf("Enter the polynomial coefficients: ");
	for (int i = 0, n = polynom->deg + 1; i < n; ++i) {
		scanf_s("%d", (polynom->coef + i));
	}
	return polynom;
}
void setX(Polynomial* polynom, int x) {
	polynom->x = x;
	if (polynom->value) {
		free(polynom->value);
	}
	polynom->value = NULL;
}
int valueOf(Polynomial* polynom) {
	if (polynom->value) {
		return polynom->value[0];
	}
	else {
		printf("Requested value isn't calculated\n");
		return 0;
	}
}