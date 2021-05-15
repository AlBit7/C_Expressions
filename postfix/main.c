#include <stdio.h>
#include "infixToPostfix.h"
#include "solvePostfix.h"

#define NUMERO_TEST 1

typedef struct test
{

    char *espressione;
    double risultato;

} TEST;

int main()
{

    TEST prova[NUMERO_TEST] = {

        {.espressione = "",
         .risultato = 8},

    };

    for (int i = 0; i < NUMERO_TEST; ++i)
    {

        double *parsato = (double *)malloc(500);
        init(prova[i].espressione, parsato); // infix --> postfix
        double ris = risolvi(parsato);

        if (ris == prova[i].risultato)
            puts("OK");
        else
            printf("%lf al posto di %lf\n", ris, prova[i].risultato);

        free(parsato);
    }

    return 0;
}