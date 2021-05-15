#include "stack.h"
#include <math.h>

#ifndef ULTIMO_ELEMENTO
#define ULTIMO_ELEMENTO -8
#endif

double calcola(double op, double e1, double e2)
{
    switch ((int)op)
    {
    case -7:
        return e1 + e2;
        break;
    case -6:
        return e1 - e2;
        break;
    case -5:
        return e1 * e2;
        break;
    case -4:
        return e1 / e2;
        break;
    case -3:
        return pow(e1, e2);
        break;

    default:
        return 0;
        break;
    }
}

double risolvi(double *postfix)
{
    Stack tmp = NULL;
    for (; *postfix != -8; ++postfix)
    {

        if (*postfix > 0)
        {
            push(&tmp, *postfix);
        }
        else
        {

            double e2 = pop(&tmp); // elemento a destra
            double e1 = pop(&tmp); // elemento a sinistra

            push(&tmp, calcola(*postfix, e1, e2)); // push nello stack del risultato
        }
    }

    return pop(&tmp);
}
