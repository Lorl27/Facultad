// 3. Considere la siguiente definici´on de listas simplemente enlazadas de enteros, que mantiene adicionalmente un puntero al ´ultimo elemento de la lista:

typedef struct _SNodo {
    int dato;
    struct _SNodo *sig;
} SNodo;

typedef struct SList {
    SNodo *primero;
    SNodo *ultimo;
} SList;

// Reimplemente para este caso las funciones slist crear, slist agregar inicio y slist agregar final.
// ¿Detecta alguna ventaja o desventaja con la nueva definici´on?

#include <stdio.h>
#include <stdlib.h>

SList slist_crear(){
    SList lista;
    lista.primero=NULL;
    lista.ultimo=NULL;

    return lista;
}

SList slist_agregar_inicio(SList lista, int dato){
    SNodo *nodo=malloc(sizeof(SNodo));
    nodo->dato=dato;
    nodo->sig=NULL;

    lista.primero=nodo;
    if(lista.ultimo==NULL)  lista.ultimo=nodo;

    return lista;
    
}

SList slist_agregar_final(SList lista, int dato){
    SNodo *nodo=malloc(sizeof(SNodo));
    nodo->dato=dato;
    nodo->sig=NULL;

    if (lista.primero==NULL) {
        lista.primero=nodo;
    }else{
        lista.ultimo->sig = nodo;
    }

    lista.ultimo=nodo; //ultimo elemento = nodo nuevo.

    return lista;

}

///* Es más eficiente ya qye para llegar al final no tenemos que recorrer todA LA lista.