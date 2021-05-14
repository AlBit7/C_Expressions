#pragma once
#include <stdlib.h>

#ifndef STACK_VUOTO
#define STACK_VUOTO -8
#endif

typedef struct node
{
    int valore;
    struct node *next;
} node;

typedef node *Stack;

int push(Stack *stack, int vaolore)
{
    node *nuovoElemento = (node *)malloc(sizeof(node));

    if (nuovoElemento == NULL)
        return 0;

    nuovoElemento->valore = vaolore;
    nuovoElemento->next = *stack;
    *stack = nuovoElemento;

    return 1;
}

int pop(Stack *stack)
{

    if (*stack == NULL)
        return STACK_VUOTO;

    int ris = (*stack)->valore;

    node *tmp = *stack;
    *stack = (*stack)->next;
    free(tmp);

    return ris;
}

int cima(Stack *stack)
{
    if (*stack == NULL)
        return STACK_VUOTO;

    return (*stack)->valore;
}
