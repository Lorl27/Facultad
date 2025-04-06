#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

//-----

int slist_longitud(SList lista){
    int cont=0;

    if(lista==NULL){
        printf("Lista vacía\n");
        return 0;
    }

    for(SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
        cont++;
    }

    return cont;
}

void slist_concatenar(SList l1, SList l2){

     for(SNodo *nodo = l2; nodo != NULL; nodo = nodo->sig){
        // printf("%d",nodo->dato);
        slist_agregar_final(l1,nodo->dato);

    }
}

SList slist_insertar(SList lista,int dato,int pos){
    SNodo *tmp = malloc(sizeof(SNodo));
    SNodo *newN = malloc(sizeof(SNodo));
    
    int contador=0;

    for(SNodo *nodo =lista; nodo!=NULL; nodo=nodo->sig){
        
        if(contador==pos){
            tmp=nodo->sig;
            nodo->sig=newN;
            newN->dato=dato;
            newN->sig=tmp;
        }

        contador++;
        
    }

    return lista;
}
