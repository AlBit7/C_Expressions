#include "stack.h"

#ifndef LUNGHEZZA_MASSIMA_NUMERO
#define LUNGHEZZA_MASSIMA_NUMERO 20
#endif

#define ULTIMO_ELEMENTO -8
#define numero(carattere) (carattere >= '0' && carattere <= '9' || carattere == '.') ? 1 : 0

void unisci(char *stringa, char carattere)
{

    for (; *stringa; ++stringa)
        ;

    *stringa++ = carattere;
    *stringa++ = 0;
}

double numerizza(char symbol) // questo serve per capire che operazione sto eseguendo senza avere l'espressione in formato stringa
{

    switch (symbol)
    {
    case '+':
        return -7;
        break;
    case '-':
        return -6;
        break;
    case '*':
        return -5;
        break;
    case '/':
        return -4;
        break;
    case '^':
        return -3;
        break;
    case '(':
    case '[':
    case '{':
        return -2;
        break;
    case ')':
    case ']':
    case '}':
        return -1;
        break;
    default:
        return 0;
    }
}

double priorita(char symbol)
{

    switch (symbol)
    {
    case '+':
    case '-':
        return 2;
        break;
    case '*':
    case '/':
        return 3;
        break;
    case '^':
        return 4;
        break;

    default:
        return 0;
        break;
    }
}

/**
 * 
 * da sinistra a destra:
 * 
 *   -  se è un numero:
 *          lo inserisco direttamente nell'espressione postfix
 *          
 *   -  se è una parentesi aperta:
 *          push nello stack
 * 
 *   -  se è una parentesi chiusa:
 *          inserisco gli elementi dello stack nel postfix fino a che trovo una parentesi aperta
 * 
 *   -  se è un operatore:
 *          - se ha più precedenza dell'operatore in cima allo stack:
 *                  push nello stack
 *          - se ha meno precedenza dell'operatore in cima allo stack:
 *                  inserisco gli elementi nel postfix (dallo stack) fino a che trovo un operatore con meno precedenza di quello che sto valutando. Infine inserisco questo operatore nello stack
 * 
 *   -  pop di tutti gli elementi da inserire nel postfix
*/

void init(char *str, double *postfix)
{

    Stack tmp = NULL;

    for (; *str; ++str)
    {

        switch (*str)
        {

        case '(':
        case '[':
        case '{':
            push(&tmp, 40);
            break;

        case ')':
        case ']':
        case '}':
        {
            double t = 0;
            while ((t = pop(&tmp)) != (double)'(') // fino a che trovo una parentesi aperta
            {
                *postfix = numerizza(t); // inserisco gli elementi nel postfix
                ++postfix;
            }

            break;
        }

        default:

            if (numero(*str)) // numero
            {

                char num[LUNGHEZZA_MASSIMA_NUMERO] = {0};

                while (1) // immagazino il numero a più cifre
                {
                    unisci(num, *str); // i caratteri del numero vengono immagazzinati in tmp
                    if (numero(*(str + 1)))
                        ++str; // finchè il numero finisce
                    else
                        break;
                }

                sscanf(num, "%lf", postfix++); // tmp viene convertito in un int
            }
            else // operatore
            {

                while (priorita(cima(&tmp)) >= priorita(*str))
                {
                    *postfix = numerizza(pop(&tmp));
                    ++postfix;
                }

                push(&tmp, *str);
                // if (cima(&tmp) < precedenza(*str)) // operatore con più precedenza dell'operatore in cima allo stack
                // {
                //     push(&tmp, precedenza(*str));
                // }
                // else // operatore con meno precedenza dell'operatore in cima allo stack
                // {
                //     while (cima(&tmp) > precedenza(*str)) // fino a che trovo un operatore con meno precedenza di quello che sto valutando
                //         postfix[j++] = pop(&tmp);         // inserisco gli elementi nel postfix (dallo stack)

                //     push(&tmp, precedenza(*str)); // inserisco questo operatore nello stack
                // }
            }

            break;
        }
    }

    while (cima(&tmp) != STACK_VUOTO) // finchè lo stack non è vuoto
    {
        *postfix = numerizza(pop(&tmp)); // inserisco tutti gli elementi
        ++postfix;
    }

    *postfix = ULTIMO_ELEMENTO;

    free(tmp);
}
