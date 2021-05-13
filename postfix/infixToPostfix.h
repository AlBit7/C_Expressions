#include "stack.h"

#ifndef LUNGHEZZA_MASSIMA_NUMERO
#define LUNGHEZZA_MASSIMA_NUMERO 20
#endif

#define numero(carattere) (carattere >= '0' && carattere <= '9') ? 1 : 0

void unisci(char *stringa, char carattere)
{

    for (; *stringa; ++stringa)
        ;

    *stringa++ = carattere;
    *stringa++ = 0;
}

int numerizza(char symbol) // questo serve per capire che operazione sto eseguendo senza avere l'espressione in formato stringa
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
        return -2;
        break;
    case ')':
        return -1;
        break;
    default:
        return 0;
    }
}

int priorita(char x)
{
    if (x == '+' || x == '-')
        return 2;
    if (x == '*' || x == '/')
        return 3;
    if (x == '^')
        return 4;
    return 0;
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

void init(char *str, int *postfix)
{

    Stack tmp = NULL;

    for (; *str; ++str)
    {

        switch (*str)
        {

        case '(':
            push(&tmp, *str);
            break;

        case ')':
        {
            int t = 0;
            while ((t = pop(&tmp)) != '(') // fino a che trovo una parentesi aperta
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

                sscanf(num, "%d", postfix++); // tmp viene convertito in un int
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

    free(tmp);
}
