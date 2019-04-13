#include "polynom.h"

void freePolynom(Polynomial** polynom) {
	free(polynom[0]->coef);
	free(polynom[0]->value);
	free(polynom[0]);
}