#include <stdio.h>
#include "dlist.h"
#include <stdlib.h>

DList crear(){
    DList lista= malloc(sizeof(DListEstructura));
    if(lista!=NULL){
        lista->primero=NULL;
        lista->ultimo=NULL;
    }
    return lista;
}

void destruir(DList lista){
    if(lista!=NULL){
        DNodo * nodo=lista->primero;
        DNodo * tmp;
        while(nodo!=NULL){
            tmp=nodo;
            nodo=nodo->sig;
            free(tmp);
        }
        free(lista);
    }
}

int es_vacia(DList lista) {
    return lista==NULL || lista->primero == NULL;
}

int longitud(DList lista){
    if (lista==NULL || lista->primero==NULL) return 0;

    int contador=0;
    for (DNodo *tmp = lista->primero; tmp != NULL; tmp = tmp->sig) {
        contador++;
    }
    return contador;
}

DList insertar(DList lista, int pos, int dato){
    if(pos<0 || pos>longitud(lista)) return lista;

    if(pos==0){
        DNodo * nuevo = malloc(sizeof(DNodo));
        nuevo->dato=dato;
        nuevo->ant=NULL;
        nuevo->sig=lista->primero;

        //la lista puede ser vacia!
        if(lista->primero!=NULL)lista->primero->ant=nuevo;

        lista->primero=nuevo;

        if(lista->ultimo==NULL) lista->ultimo=nuevo;

        return lista;
    }

    if(lista==NULL || lista->primero==NULL) return lista;

    int contador=1;
    DNodo * inicio=lista->primero;
    DNodo * actual=lista->primero->sig;

    while(inicio!=NULL && contador<pos){
        inicio=actual;
        actual=actual->sig;
        contador++;
    }

    if(inicio!=NULL && contador==pos){
        DNodo * nuevo = malloc(sizeof(DNodo));
        nuevo->dato=dato;
        nuevo->ant=inicio;
        nuevo->sig=actual;
        inicio->sig=nuevo;

        if(actual==NULL) {
            lista->ultimo=nuevo;
        }else{
            actual->ant=nuevo;
        }
    }

    return lista;
}


DList eliminar(DList lista, int pos){
if(pos<0 || pos>=longitud(lista)) return lista;

    if(pos==0){
        DNodo *tmp= lista->primero;
        lista->primero=lista->primero->sig;

        if(lista->primero==NULL) lista->ultimo=NULL;
        else lista->primero->ant=NULL;

        free(tmp);

        return lista;
    }
    
    if(lista==NULL || lista->primero==NULL) return lista;

    int contador=1;
    DNodo * inicio=lista->primero;
    DNodo * actual=lista->primero->sig;

    while(actual!=NULL && contador<pos){
        inicio=actual;
        actual=actual->sig;
        contador++;
    }

    //inicio->sig el que quiero borrar.
    if(actual!=NULL && contador==pos){
       inicio->sig=actual->sig;
       if(actual->sig==NULL) lista->ultimo=inicio;
       else  actual->sig->ant=inicio;

       free(actual);

        
    }

    return lista;
}

void recorrer(DList lista, DListOrdenDeRecorrido orden, funcionRecorredora funcion){
    if(lista!=NULL){

        if(orden==DLIST_RECORRIDO_HACIA_ADELANTE){
            DNodo * tmp;
            for(tmp=lista->primero;tmp!=NULL;tmp=tmp->sig){
                funcion(tmp->dato);
            }
        }

        if(orden==DLIST_RECORRIDO_HACIA_ATRAS){
            DNodo * tmp;
            for(tmp=lista->ultimo;tmp!=NULL;tmp=tmp->ant){
                funcion(tmp->dato);
            }
        }

    }
}

DList reverso(DList lista){
    if(lista==NULL || lista->primero==NULL) return lista;

    DList lista_reversa=crear();

    for(DNodo *tmp=lista->primero;tmp!=NULL;tmp=tmp->sig){
        lista_reversa=insertar(lista_reversa,0,tmp->dato);
    }

    return lista_reversa;
}
