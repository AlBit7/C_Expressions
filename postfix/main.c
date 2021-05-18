#include <stdio.h>
#include "infixToPostfix.h"
#include "solvePostfix.h"

#define NUMERO_TEST 4
#define BUFFER 250

typedef struct test
{

    char *espressione;
    double risultato;

} TEST;

int main()
{

    TEST prova[NUMERO_TEST] = {

        {.espressione = "8",
         .risultato = 8},
        {.espressione = "90.4-6.87",
         .risultato = 83.53},
        {.espressione = "36.5+(49-23*2)^2",
         .risultato = 45.5},
        {.espressione = "(2.1^2+5.2-7.2)*7.1",
         .risultato = 17.111},

    };

    for (int i = 0; i < NUMERO_TEST; ++i)
    {

        double *parsato = (double *)malloc(BUFFER);
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
