#include "cdlist.h"
#include <stdio.h>
#include <stdlib.h>

CDList crear(){
    CDList lista = malloc(sizeof(CDListEstructura));
    if(lista!=NULL){
        lista->primero=NULL;
    }
    return lista;
}

void destruir(CDList lista){
    if(lista==NULL) return;

    if(lista->primero!=NULL){

    DNodo  * inicio = lista->primero;
    DNodo * nodo=lista->primero;
    DNodo * tmp;
    do{
        tmp=nodo;
        nodo=nodo->sig;
        free(tmp);
    }
    while(nodo!=inicio);
    }

    free(lista);

}


int es_vacia(CDList lista) {
    return lista==NULL || lista->primero == NULL;
}

int longitud(CDList lista){
    if (lista==NULL || lista->primero==NULL) return 0;

    int contador=0;
    DNodo *tmp = lista->primero;
    do{
        contador++;
        tmp=tmp->sig;
    }while(tmp!=lista->primero);

    return contador;
}

CDList insertar(CDList lista, int pos, int dato){
    if(pos<0 || pos>longitud(lista)) return lista;


    DNodo * nuevo = malloc(sizeof(DNodo));
    nuevo->dato=dato;
    

    // CASO A: Lista vacía (Se abraza a sí mismo)
    if (lista->primero == NULL) {
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        lista->primero = nuevo;
        return lista;
    }

    if(pos==0){
        DNodo *ultimo = lista->primero->ant;

        nuevo->sig = lista->primero;
        nuevo->ant = ultimo;
        
        lista->primero->ant = nuevo;
        ultimo->sig = nuevo;

        lista->primero=nuevo;

        return lista;
    }

    if(lista==NULL || lista->primero==NULL) return lista;

    

    int contador=1;
    DNodo * inicio=lista->primero;
    DNodo * actual=lista->primero->sig;

    while( contador<pos){
        inicio=actual;
        actual=actual->sig;
        contador++;
    }

    if(contador==pos){
        DNodo * nuevo = malloc(sizeof(DNodo));
        nuevo->dato=dato;

        nuevo->ant=inicio;
        nuevo->sig=actual;

        inicio->sig=nuevo;
        actual->ant=nuevo;
        
    }

    return lista;
}


CDList eliminar(CDList lista, int pos){
if(pos<0 || pos>=longitud(lista)) return lista;


// CASO ESPECIAL: Solo queda 1 elemento en toda la lista
    if (lista->primero->sig == lista->primero) {
        free(lista->primero);
        lista->primero = NULL;
        return lista;
    }

    if(pos==0){
        DNodo *tmp= lista->primero;
        DNodo * ult=tmp->ant;
        DNodo * prim=tmp->sig;

        ult->sig=prim;
        prim->ant=ult;

        lista->primero=prim;

        free(tmp);

        return lista;
    }
    
    if(lista==NULL || lista->primero==NULL) return lista;

    int contador=1;
    DNodo * inicio=lista->primero;
    DNodo * actual=lista->primero->sig;

    while(contador<pos){
        inicio=actual;
        actual=actual->sig;
        contador++;
    }

    //inicio->sig el que quiero borrar.
    if( contador==pos){
       inicio->sig=actual->sig;
       actual->sig->ant=inicio;

       free(actual);

        
    }

    return lista;
}

void recorrer(CDList lista, CDListOrdenDeRecorrido orden, funcionRecorredora funcion){
    if(lista!=NULL && lista->primero!=NULL){

        if(orden==CDList_RECORRIDO_HACIA_ADELANTE){
            DNodo * tmp=lista->primero;
            do {
            funcion(tmp->dato);
            tmp = tmp->sig;
        } while (tmp != lista->primero); // Frenamos al dar la vuelta
        }

        if(orden==CDList_RECORRIDO_HACIA_ATRAS){
            DNodo * tmp=lista->primero->ant;
            do {
            funcion(tmp->dato);
            tmp = tmp->ant;
        } while (tmp != lista->primero->ant); // Frenamos al volver al final.
        }

    }
}

CDList reverso(CDList lista){
    if(lista==NULL || lista->primero==NULL) return lista;

    CDList lista_reversa=crear();

    DNodo *tmp=lista->primero;
    do{
        lista_reversa=insertar(lista_reversa,0,tmp->dato);
        tmp=tmp->sig;
    }while(tmp!=lista->primero);
    

    return lista_reversa;
}


