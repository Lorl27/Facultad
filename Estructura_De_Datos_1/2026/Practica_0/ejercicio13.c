#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
La baraja española es un conjunto tradicional de 48 naipes, 
divididos en cuatro palos (oros, copas, espadas y bastos) 
con numeración del 1 al 9  y 
tres figuras: sota (10), caballo (11) y rey (12). */

typedef enum { ORO, COPA, ESPADA, BASTO } Palo;

typedef struct{
    Palo palo;
    int numero;
} Carta;

typedef struct{
    Carta cartas[48];
} Mazo;

//max 12 x 4 palos.
void llenar(Mazo *mazo){
    int indice = 0;
    for (int p = ORO; p <= BASTO; p++) {
        for (int num = 1; num <= 12; num++) {
            mazo->cartas[indice].palo = p;
            mazo->cartas[indice].numero = num;
            indice++;
        }
    }
}

Carta azar(Mazo mazo){
    int numero_r=rand() % 48 + 0;
    return(mazo.cartas[numero_r]);
}


int main(){
    srand(time(NULL));
    Mazo mi_mazo;
    llenar(&mi_mazo);
    Carta c = azar(mi_mazo);
    printf("Sacaste un %d\n", c.numero);

    return 0;
}

