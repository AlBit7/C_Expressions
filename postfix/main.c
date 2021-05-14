#include <stdio.h>
#include "infixToPostfix.h"
#include "solvePostfix.h"

int main()
{

    char *es = (char *)"((15/(7-(1+1)))*3)-(2+(1+1))";
    int *parsato = (int *)malloc(150);

    init(es, parsato); // infix --> postfix

    printf("%s --> ", es);
    for (int i = 0; parsato[i] != ULTIMO_ELEMENTO; ++i)
    {
        printf("%d ", parsato[i]);
    }

    printf("\nrisutato: %d", risolvi(parsato));

    free(parsato);
    return 0;
}
