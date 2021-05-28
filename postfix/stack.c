#include "stack.h"

typedef struct myNode
{
    double valore;
    struct myNode *next;
} node;

void push(Stack *stack, double vaolore)
{
    node *nuovoElemento = (node *)malloc(sizeof(node));

    nuovoElemento->valore = vaolore;
    nuovoElemento->next = *stack;
    *stack = nuovoElemento;
}

double pop(Stack *stack)
{

    if (*stack == NULL)
        return STACK_VUOTO;

    double ris = (*stack)->valore;

    node *tmp = *stack;
    *stack = (*stack)->next;
    free(tmp);

    return ris;
}

double cima(Stack *stack)
{
    if (*stack == NULL)
        return STACK_VUOTO;

    return (*stack)->valore;
}
