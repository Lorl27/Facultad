// TAREA: usa glist para hacer pila.

#include "../Practica_2/glist/glist.h"
#include <stdio.h>
#include <stdlib.h>

typedef GList Pila;

Pila pila_crear(){
    Pila pila=glist_crear();
    return pila;
}

Pila Pop(Pila pila, FuncionDestructora destroy){
    pila=glist_eliminar_elemento_recursivamente(pila,destroy,0);
    return pila;
}

Pila Push(Pila pila , void * elemento, FuncionCopia copy){
    pila= glist_agregar_inicio(pila,elemento,copy);
    return pila;
}

int isEmpty(Pila pila){
    return glist_vacia(pila);
}

Pila  pila_destruir(Pila pila,FuncionDestructora destroy){
    glist_destruir(pila,destroy);
    return NULL;
}

void pila_recorrer(Pila pila, FuncionVisitante fun){
    glist_recorrer(pila,fun);
}

void * Top(Pila pila){
    if (isEmpty(pila)) return NULL;
    return pila->data;
}