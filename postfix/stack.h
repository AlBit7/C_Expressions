#ifndef _STACK_
#define _STACK_

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

void push(Stack *stack, double vaolore);
double pop(Stack *stack);
double cima(Stack *stack);

#endif
