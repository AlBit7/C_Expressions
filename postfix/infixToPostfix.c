#include "infixToPostfix.h"

void unisci(char *stringa, char carattere)
{

    for (; *stringa; ++stringa)
        ;

    *stringa++ = carattere;
    *stringa++ = 0;
}

double numerizza(char symbol)
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