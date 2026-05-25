#include "pila.h"
#include <stdio.h>
#include <stdlib.h>


Pila pila_crear(){
    Pila  pila = malloc(sizeof(struct _Pila));
    if(pila!=NULL){
        pila->inicio= NULL;
    }
    return pila;
}

int isEmpty(Pila  pila){
    return pila==NULL || pila->inicio == NULL;
}


void * Top(Pila pila){
    if(isEmpty(pila)) return NULL;

    return pila->inicio->dato;
}

Pila  Pop(Pila  pila, FuncionDestructora destroy){
    if(isEmpty(pila)) return pila;

    SNodo * topeActual = pila->inicio;
    pila->inicio=pila->inicio->sig;
    destroy(topeActual->dato);
    free(topeActual);

    return pila;
}

Pila  Push(Pila  pila, void * elemento, FuncionCopia copy){
    if (pila == NULL) return NULL;

    SNodo * topeActual = pila->inicio;
    SNodo * nuevoTope=malloc(sizeof(SNodo));
    nuevoTope->dato=copy(elemento);
    nuevoTope->sig=topeActual;
    pila->inicio=nuevoTope;

    return pila;
}


Pila pila_destruir(Pila pila, FuncionDestructora destroy){
    if (pila == NULL) return NULL;

    while (!isEmpty(pila)) {
        pila = Pop(pila, destroy);
    }
    free(pila);
    
    return NULL;
}


// con esta ver, no hace falta poner pila=NULL .
// pero debemos llamar con &pila
// void pila_destruir(Pila * pila, FuncionDestructora destroy){
//     while (!isEmpty(*pila)) {
//         *pila = Pop(*pila, destroy);
//     }
//     free(*pila);
//     *pila = NULL;    
// }


void pila_recorrer(Pila pila, FuncionVisitante fun){
    for(SNodo * tmp=pila->inicio;tmp!=NULL;tmp=tmp->sig){
        fun(tmp->dato);
    }
}