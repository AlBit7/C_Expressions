#include <stdio.h>
#include "infixToPostfix.h"

int main()
{

    char *es = (char *)"2*20/2+(3+4)*3^2-6+15";
    int *parsato = (int *)malloc(150);

    init(es, parsato); // infix --> postfix

    printf("%s --> ", es);
    for (int i = 0; i < 18; i++)
    {
        printf("%d ", parsato[i]);
    }

    free(parsato);

    return 0;
}
