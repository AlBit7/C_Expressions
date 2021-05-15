#include <math.h>
#include "stack.h"

#ifndef ULTIMO_ELEMENTO
#define ULTIMO_ELEMENTO -8
#endif

double calcola(double op, double e1, double e2);
double risolvi(double *postfix);