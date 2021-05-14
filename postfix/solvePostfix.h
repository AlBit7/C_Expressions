#include "stack.h"

#ifndef ULTIMO_ELEMENTO
#define ULTIMO_ELEMENTO -8
#endif

int calcola(int op, int e1, int e2)
{
    switch (op)
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
        return e1 ^ e2;
        break;

    default:
        return 0;
        break;
    }

    
}

int risolvi(int *postfix)
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

            int e2 = pop(&tmp); // elemento a destra
            int e1 = pop(&tmp); // elemento a sinistra

            push(&tmp, calcola(*postfix, e1, e2)); // push nello stack del risultato
        }
    }

    return pop(&tmp);
}
