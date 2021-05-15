#include <stdio.h>
#include "stack.h"

#ifndef LUNGHEZZA_MASSIMA_NUMERO
#define LUNGHEZZA_MASSIMA_NUMERO 20
#endif

#define ULTIMO_ELEMENTO -8 // "carattere" terminatore
#define numero(carattere) (carattere >= '0' && carattere <= '9' || carattere == '.') ? 1 : 0 // macro per riconoscere parte di un numero

void   unisci(char *stringa, char carattere); // unisce un carattere ad una stringa
double numerizza(char symbol); // questo serve per capire che operazione sto eseguendo senza avere l'espressione in formato stringa
double priorita(char symbol);

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

void init(char *str, double *postfix);