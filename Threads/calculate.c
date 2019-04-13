#include "polynom.h"
#include <stdio.h>

void calculate(Polynomial* polynom) {
	if (polynom->value) {
		free(polynom->value);
	}
	polynom->value = (int*)calloc(sizeof(int));
	for (int i = polynom->deg, powX = 1; i >= 0; --i, powX *= polynom->x) {
		polynom->value[0] += polynom->coef[i] * powX;
	}
	printf("p(%d) = %d\n", polynom->x, polynom->value[0]);
}