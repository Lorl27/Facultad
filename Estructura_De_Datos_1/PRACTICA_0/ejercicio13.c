// 13. Suponga que tiene que implementar un juego que requiere utilizar un mazo de cartas. Implemente
// los siguientes puntos para crear una representaci ́on del mismo que luego pueda utilizarse para el juego:
// a) Defina un tipo de datos Carta para representar una carta de la baraja espa ̃nola. Represente el
// palo con una enumeraci ́on.
// b) Defina un tipo de datos Mazo como un arreglo de 48 cartas.
// c) Implemente una funci ́on void llenar(Mazo) que tome un mazo y lo llene con las cartas corre-
// spondientes.
// d) Implemente una funci ́on Carta azar(Mazo) que reciba un mazo y devuelva una carta al azar
// del mismo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{
    ORO, //0
    COPAS,
    ESPADAS,
    BASTO  //3
} Palo_carta;

typedef struct {
    int valor;  // Valores del 1(AS) al 12(SOTA-CABALLO-REY) (sin 8 ni 9 en la baraja española)
    Palo_carta palo;  
} Carta;

typedef struct{
    Carta cartas[48];
} Mazo;

void llenar(Mazo *m){
    int index=0;

    for(int palo=ORO; palo<=BASTO; palo++){ //Iteramos todos los palos
        for(int valor=1;valor<=12;valor ++){
            if(valor!=8 && valor!=9){
                m->cartas[index].valor=valor;
                m->cartas[index].palo= (Palo_carta)palo; //lo casteamos.
                index++;
            }
        }
    }
}

Carta azar(const Mazo *m){
    int rnd=rand() %48;
    return m->cartas[rnd];
}

void imprimir_carta(Carta c){
    const char *palos[]={"Oro","Copas","Espadas","Basto"};
    printf("%d de %s \n",c.valor, palos[c.palo]);
}


int main(){
    srand(time(NULL));

    Mazo mazo;
    llenar(&mazo);

    Carta c=azar(&mazo);
    imprimir_carta(c);

    return 0;

}