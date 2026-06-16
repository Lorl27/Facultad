typedef struct {
    char* pais;
    char* ciudad;
    int cantidadHabitantes;
    int importancia;
} Objetivo;

typedef struct nodo{
    Objetivo dato;
    struct nodo* anterior;
    struct nodo* siguiente;
} Nodo;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo * agregarObjetivo(Nodo * inicio, Objetivo o){
    Nodo * nuevo = malloc(sizeof(struct nodo));
    nuevo->dato=o;
    
    if(inicio==NULL){
        nuevo->anterior=nuevo;
        nuevo->siguiente=nuevo;
        return nuevo;
    }

    Nodo * ultimo = inicio->anterior;

    ultimo->siguiente = nuevo;
    nuevo->anterior = ultimo;
    nuevo->siguiente = inicio;
    inicio->anterior = nuevo;

    return inicio;

}

void mostrarCantidadHabitantesPorPais(Nodo * inicio, char * pais){
    if(!inicio || inicio->dato.pais==NULL) {
        printf("NO hay objetivo presente\n");
        return;
    }

    int total=0;
    Nodo * tmp = inicio;

    do{
        if(strcmp(tmp->dato.pais,pais)==0){
            total+=tmp->dato.cantidadHabitantes;
        }
        tmp=tmp->siguiente;
    }
    while(tmp!=inicio);
    

    if(total==0) printf("No hay objetivo presente para ese pais. \n");
    printf("El total de habitantes en el pais %s es: %d \n",pais,total);

    
}