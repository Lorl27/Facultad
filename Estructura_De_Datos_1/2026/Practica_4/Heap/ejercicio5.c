#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"


/* Retorna 1 si la cola esta vacio y, 0 en caso contrario*/
int cola_prioridad_es_vacia(BHeap cola){
    return bheap_es_vacio(cola);
}

/* Retorna el elemento prioritario de la cola*/
void * cola_prioridad_maximo(BHeap cola){
    return bheap_obtener_maximo(cola);
}

/* Elimine el elemento prioritario de la cola*/
BHeap cola_prioridad_eliminar_maximo(BHeap cola, FuncionComparadora comp, FuncionDestructora destroy){
    return bheap_eliminar_maximo(cola,comp,destroy);
}

/* Inserte un elemento en la cola con  determinada prioridad*/
BHeap cola_prioridad_insertar(BHeap cola, void * elemento, FuncionCopiadora copy, FuncionComparadora comp){
    return bheap_insertar(cola,elemento,copy,comp);
}
