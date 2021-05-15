#pragma once
#include <stdlib.h>

#ifndef STACK_VUOTO
#define STACK_VUOTO -8
#endif

typedef struct node
{
    double valore;
    struct node *next;
} node;

typedef node *Stack;

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
