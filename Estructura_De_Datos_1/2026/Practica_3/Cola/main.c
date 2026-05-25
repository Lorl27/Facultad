#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

int * copiar_entero(int *entero){
 int *copia=malloc(sizeof(int));
 *copia=*entero;
 return copia;
}

void destruir_enteros(int *entero){
    free(entero);
}

int main(){
    Cola cola=Cola_crear();

    printf("¿La cola está vacía? %s\n", isEmpty(cola) ? "Sí" : "No");

    printf("Insertemos elementos...");

    int a=20;
    int b=560;
    int c=0;
    cola=Encolar(cola,&a,(FuncionCopia)copiar_entero);
    cola=Encolar(cola,&b,(FuncionCopia)copiar_entero);
    cola=Encolar(cola,&c,(FuncionCopia)copiar_entero);

    printf("¿La cola está vacía? %s\n", isEmpty(cola) ? "Sí" : "No");

    printf("ELiminemos el ultimo\n");
    cola=Desencolar(cola,(FuncionDestructora)destruir_enteros);

    cola=cola_destruir(cola,(FuncionDestructora)destruir_enteros);

    printf("¿La cola está vacía? %s\n", isEmpty(cola) ? "Sí" : "No");


    return 0;


}