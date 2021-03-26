#include <math.h> // per fare la potenza

#define BUFFER 150                                                                           // indicativamente dovrebbe essere più di metà dei caratteri dell'espressione
#define numero(carattere) (carattere >= '0' && carattere <= '9' || carattere == '.') ? 1 : 0 // macro per capire se un carattere appartiene a un numero o meno
#define operazione(carattere) (carattere == '^' || carattere == '/' || carattere == '*' || carattere == '-' || carattere == '+') ? 1 : 0

typedef struct ESP {

    double numeri[BUFFER];
    char   operazioni[BUFFER];
    int    lunghezza;

} ESP;

void   init    (ESP * esp, char * espressione);             // inizializza lo struct a partire dalla stringa "espressione"
double risolvi (char * stringa);                            // funzione principale
int    trova   (char * stringa, char carattere, int fine);  // restituisce la posizione del carattere indicato in una stringa, se non trova niente restituisce -1
void   unisci  (char * stringa, char carattere);            // aggiunge un carattere ad una stringa (a patto che sia allocata abbastanza memoria)
void   pop     (ESP * esp, int daEliminare);                // elimina dallo struct ESP le operazioni già svolte
char * sistema (char * espressione);

double risolvi(char * stringa) {

    // ------ DICHIARAZIONE ED INIZIALIZZAZIONE ------

    ESP espressione;

    init(&espressione, stringa);

    // ------ CALCOLI ------

    int tmp;

    for (char * operazioni = "^/*-+"; *operazioni; ++operazioni) { // itero la stringa con le operazioni da risolvere

        while (1) { // fino a quando l'operazione che ha la priorità non sarà più presente nell'array espressione.operazioni 

            tmp = trova(espressione.operazioni, *operazioni, espressione.lunghezza); if (tmp == -1) break;

            switch (*operazioni) {

                case '^': espressione.numeri[tmp] = pow(espressione.numeri[tmp], espressione.numeri[tmp + 1]); break;
                case '/': espressione.numeri[tmp] /= espressione.numeri[tmp + 1];                              break;
                case '*': espressione.numeri[tmp] *= espressione.numeri[tmp + 1];                              break;
                case '-': espressione.numeri[tmp] -= espressione.numeri[tmp + 1];                              break;
                case '+': espressione.numeri[tmp] += espressione.numeri[tmp + 1];                              break;
                
                default: break;

            }
            
            pop(&espressione, tmp + 1); // elimino dall'espressione i termini che non mi servono più (sia numeri che operazioni) e diminuisco la lunghezza
        
        }

    }

    return espressione.numeri[0]; // restituisco il primo valore, ovvero l'unico rimasto

}

void init(ESP * esp, char * espressione) {
    
    int iteratoreOperazioni, iteratoreNumeri, i = 0, numeroNegativo = 0; iteratoreOperazioni = iteratoreNumeri = -1;
    char tmp[BUFFER] = { 0 };

    for ( ; espressione[i] != '\0'; ++i) { // itera l'espressione

        if (operazione(espressione[i])) {      // operazioni

            if ((espressione[i] == '-' && !numero(espressione[i-1])) && espressione[i-1] != ')') numeroNegativo = 1; // segno - come numero negativo
            else esp -> operazioni[++iteratoreOperazioni] = espressione[i];                                          // aggiungi operazione

        } else if (numero(espressione[i])) {    // numeri

            if (numeroNegativo) {
                unisci(tmp, '-');
                numeroNegativo = 0;
            }

            while (1) {                                   
                unisci(tmp, espressione[i]);        // i caratteri del numero vengono immagazzinati in tmp
                if (numero(espressione[i+1])) ++i;  // finchè il numero finisce
                else break;
            } 

            sscanf(tmp, "%lf", &esp -> numeri[++iteratoreNumeri]);     // tmp viene convertito in un double 

        } else if (espressione[i] == '(') {   // parentesi

            int parentesi = 1; // uno perchè apro una parentesi

            while (1) {

                if (espressione[++i] == '(') ++parentesi;
                else if (espressione[i] == ')') --parentesi;
                
                if (parentesi != 0) unisci(tmp, espressione[i]); // prendo tutti i caratteri che trovo nella parentesi
                else break;                                      // se la parentesi relativa viene chiusa allora esco dal loop

            }

            esp -> numeri[++iteratoreNumeri] = risolvi(tmp); // risolvi e init sono due funzioni ricursive che si chiamano a vicenda
            
            if (numeroNegativo) {
                esp -> numeri[iteratoreNumeri] *= -1;
                numeroNegativo = 0;
            }

        }

        tmp[0] = '\0'; // faccio finta che l'array sia vuoto (perchè le stringhe di prima non mi interessano più nella prossima iterazione)

    }
 
    esp -> lunghezza = iteratoreNumeri + 1; // inizializzo la lunghezza

}

// --------------------------------------------------------------

void pop(ESP * esp, int daEliminare) {

    for ( ; daEliminare < esp -> lunghezza; ++daEliminare) {

        esp -> numeri    [daEliminare] = esp -> numeri    [daEliminare + 1];
        esp -> operazioni[daEliminare - 1] = esp -> operazioni[daEliminare];

    } // so che non è molto efficente come metodo ma per questo programma penso possa andare bene

    esp -> numeri[daEliminare - 1] = 0;
    esp -> operazioni[daEliminare] = '\0'; 

    esp -> lunghezza--;

}

void unisci(char * stringa, char carattere) {

    for( ; *stringa; ++stringa);  
    
    *stringa++ = carattere; 
    *stringa++ = 0;
  
}

int trova(char * stringa, char carattere, int fine) {

    for (int i = 0; i < fine; ++i) 
        if (stringa[i] == carattere)
            return i;

    return -1;

}

char * sistema(char * espressione) { 

    unsigned int numeroParentesiAperte = 0;

    static char risultato[BUFFER];
    int i = -1;

    for ( ; *espressione; ++espressione) {

        if (*espressione != ' ' && (numero(*espressione) || operazione(*espressione))) risultato[++i] = *espressione;   // tolgo gli spazzi e caratteri invalidi
        
        else if (*espressione == '{' || *espressione == '[' || *espressione == '(') {
            
            risultato[++i] = '(';  
            ++numeroParentesiAperte;

        } else if (*espressione == '}' || *espressione == ']' || *espressione == ')') {
            
            risultato[++i] = ')';   
            --numeroParentesiAperte;

        }

    }

    risultato[++i] = '\0';

    char invalido = '\0';
    return (numeroParentesiAperte == 0) ? risultato : &invalido;

}