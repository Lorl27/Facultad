#ifndef __PILA_CON_ARREGLOS_ENTEROS_H__
#define __PILA_CON_ARREGLOS_ENTEROS_H__

#include "ArregloEnteros.h"

struct _Pila {
    ArregloEnteros *arr;
    int ultimo; // indice del tope de la Pila! ; -1: vacia!
};

typedef struct _Pila *Pila;

/*
* Crea e inicializa una nueva pila vacıa con la capacidad dada.
*/
Pila pila_crear(int capacidad);

/*
* Libera la memoria requerida para la pila.
*/
void pila_destruir(Pila pila);

/*
* Retorna 1 si la pila esta vacıa, y 0 en caso contrario.
*/
int pila_es_vacia(Pila pila);

/*
* Retorna el elemento que se encuentre en el tope de la pila, pero sin eliminarlo.
*/
int pila_tope(Pila pila);

/*
* Inserta un elemento en el tope de la pila, 
en caso que la pila se encuentre llena debera aumentar al doble la capacidad del arreglo.
*/
void pila_apilar(Pila pila, int elemento);

/*
* Elimina el elemento que se encuentra en el tope de la pila.
*/
void pila_desapilar(Pila pila);

/*
* Imprime en orden los elementos de la pila.
*/
void pila_imprimir(Pila pila);

#endif