#include <stdio.h>
#include "risolvi.h"

#define NUMERO_TEST 13

typedef struct test {
        
    char * espressione;
    double risultato;

} TEST;

int main() {
    
    TEST prova[NUMERO_TEST] = {

        {
            .espressione = "0----1",
            .risultato   = 1
        },

        {
            .espressione = "7--7",
            .risultato   = 14
        },

        {
            .espressione = "-(-7)",
            .risultato   = 7
        },

        {
            .espressione = "-((-1)-1)",
            .risultato   = 2
        },

        {
            .espressione = "-23-(-11+(-6-(-15+8)+(-24+6))-(32-24))",
            .risultato   = 13
        },

        {
            .espressione = "-3648.54376+((((((1+((1*(1))*1))^0))))+3648.54376)",
            .risultato   = 1
        },

        {
            .espressione = "64^((-1+-1+-1-1+0-1-1+6)+(368756.374265^0)/(12/2-4))",
            .risultato   = 8
        },

        {
            .espressione = "-(6*(-7-(9-5)*(-2+15-11)+-24/-3-(2-13))-5)+(7-19)/2", 
            .risultato   = -25
        },

        {
            .espressione = "(((5/6-1-3/2+2)^5/(1/2-7/3+3/2)^3)*((-1*18/6)/(3-5))^3)/(7645.836*0-(-1/3)^3/(3/4-1/2+(2^3-(-1*-3))/12)^2-(3/11-4/3)*-11/14)",
            .risultato   = 0.5
        },
        
        // Test per la funzione "sistema"
        
        {
            .espressione = "1 + 1",
            .risultato   = 2
        },

        {
            .espressione = "1 +a1",
            .risultato   = 2
        },

        {
            .espressione = "{ [(1) ciao ciao ]}",
            .risultato   = 1
        },

        {
            .espressione = "(()))",
            .risultato   = '\0'
        }

    };

    for (int i = 0; i < NUMERO_TEST; ++i) {

        double ris = risolvi(sistema(prova[i].espressione));

        if (ris == prova[i].risultato) puts("OK");  
        else printf("%lf al posto di %lf\n", ris, prova[i].risultato);  

        // non mi ricordo bene come comportarmi quando devo comparare i double o i float
        // perchè potrebbe succedere (come nella quartultimo test) che il risultato sia 
        // leggermente maggiore che il vero risultato (causato da un'imprecisione durante
        // il memorizzazmento di numeri decimali di base 10 in base 2)

    }

}

/*

la funzione "risolvi" supporta le seguenti operazioni:

 ^ elevamento a potenza
 / divisione
 * moltiplicazione
 - sottrazione
 + somma

l'input dev'essere una stringa esente da spazi o caratteri diversi da:

 numeri da 0 a 9
 . per numeri decimali
 le cinque operazioni elencate precedentemente
 parentesi tonde aperte o chiuse

esempio:

 2+3.4  --> valido
 2+3. 4 --> invalido

 4^(1/2) --> valido
 4^(a/2) --> invalido (sscanf non rileva il valore decimale del carattere)

l'output è un valore double (64-bit)

Note:

 - la funzione ha due dipendenze:
    
    - stdio.h --> sscanf: il modo più sicuro per convertire una stringa in un double
    - math.h --> pow: funzione per fare l'elevamento a potenza

 - non ho ancora implementato un controllo parentesi ("((1)" questa espressione non verrà risolta e causerà un buffer overload della viariabile tmp dichiarata in risolvi.h alla riga 63)

*/

/* 

La funzione "sistema" (sempre dichiarata in risolvi.h):

 - "1 + 1" --> "1+1"
 - "1 +a1" --> "1+1"
 - "{ [(1) ciao ciao ]}" --> "(((1)))"
 - "(()))" --> "\0"

*/ 
