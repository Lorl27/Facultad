#include "cdlist.h"
#include <stdlib.h>
#include <stdio.h>

CDlist Cdlist_crear() {
    CDlist lista;
    lista.ultimo=NULL;
    return lista;
}

void Cdlist_destruir(CDlist *lista) {
    if(lista==NULL || lista->ultimo==NULL) return;
    //lista->ultimo: Es el puntero que apunta al último nodo de la lista.
    //lista->ultimo->sig: Es el puntero del último nodo hacia el primer nodo de la lista (porque estamos trabajando con una lista circular).
    CDNodo *tmp=lista->ultimo->sig;  //Primer nodo 

    do{
        CDNodo *siguiente=tmp->sig; //Ok,ahora voy al 2do nodo
        free(tmp);  //Libero el primer nodo
        tmp=siguiente;  //ahora, mi nodo1 es el nodo2
    }while(tmp!=lista->ultimo->sig);  //sigo hasta llegar al final (Primer nodo, again)
    
    lista->ultimo=NULL;

}

int Cdlist_vacia(CDlist lista) {
    return lista.ultimo==NULL;
}

CDlist Cdlist_agregar_final(CDlist *lista, int dato) {

    CDNodo *nuevoNodo=malloc(sizeof(CDNodo));
    nuevoNodo->dato=dato;

    if(lista->ultimo==NULL){ //el primero es vacio, entonces ahi pongo nuevo nodo ;)
        nuevoNodo->sig=nuevoNodo;
        nuevoNodo->ant=nuevoNodo;
        lista->ultimo=nuevoNodo;  //Como soy empty, me apunto a m+i mismo...
    }else{
        CDNodo *tmp=lista->ultimo->sig; //1er nodo (ya que existe)
        nuevoNodo->ant=lista->ultimo;  //inserto el nuevo nodo entre el último
        nuevoNodo->sig=tmp;   //y el primero.

        lista->ultimo->sig=nuevoNodo;
        tmp->ant=nuevoNodo;

        lista->ultimo=nuevoNodo;
    }


    return *lista;

}


CDlist Cdlist_agregar_inicio(CDlist *lista, int dato) {
    CDNodo *nuevoNodo=malloc(sizeof(CDNodo));
    nuevoNodo->dato=dato;

    if(lista->ultimo==NULL){ //si esta vacio, entonces mi nuevo nodo es el ! que existe.
        nuevoNodo->sig=nuevoNodo;
        nuevoNodo->ant=nuevoNodo;
        lista->ultimo=nuevoNodo;
    }else{
        CDNodo *sigiente=lista->ultimo->sig; 
        nuevoNodo->sig=sigiente;
        nuevoNodo->ant=lista->ultimo;

        lista->ultimo->sig=nuevoNodo;
        sigiente->ant=nuevoNodo;
    }

    return *lista;
}

void Cdlist_recorrer(CDlist lista, FuncionVisitante visit) {
    if(Cdlist_vacia(lista)) return;

    CDNodo *inicio=lista.ultimo->sig;

    for(CDNodo *tmp=inicio; ;tmp=tmp->sig){
        visit(tmp->dato);
        if(tmp->sig==inicio) break; //circulo completado...
    }
}

//----

/* implemente CDlist recorrer de manera
que se pueda elegir si se avanza o retrocede en el recorrido, utilizando el tipo:
typedef enum {
    CdLIST_RECORRIDO_HACIA_ADELANTE,
    CdLIST_RECORRIDO_HACIA_ATRAS
 } CdListOrdenDeRecorrido; */
void Cdlist_recorrer_elegir(CDlist lista,FuncionVisitante visit, CDListOrdenDeRecorrido orden){
    if(Cdlist_vacia(lista)) return;

    switch (orden)
    {
    case CdLIST_RECORRIDO_HACIA_ADELANTE:{
        CDNodo *inicio=lista.ultimo->sig;
        for(CDNodo *tmp=inicio;;tmp=tmp->sig){
            visit(tmp->dato);
            if (tmp->sig == inicio) break;
        }
        break;}
    
    case CdLIST_RECORRIDO_HACIA_ATRAS:
        {CDNodo *inicio=lista.ultimo;
        for(CDNodo *tmp=inicio;;tmp=tmp->ant){
                visit(tmp->dato);
                if(tmp->ant==inicio) break;
            }
            break;
        }
    }
}

//-----

int Cdlist_longitud(CDlist lista){

}



//-----------------------------

void Cdlist_concatenar(CDlist *l1, CDlist *l2){
}

void Cdlist_insertar(CDlist *lista,int dato,int pos){

}

CDlist Cdlist_eliminar(CDlist lista, int pos) {

}



void Cdlist_borrar_dato(CDlist *lista, int dato) {

}


int Cdlist_contiene(CDlist lista, int dato){

}

int Cdlist_indice(CDlist lista, int elemento){

}

CDlist Cdlist_intersecar(CDlist Cdlista1, CDlist Cdlista2) {

}


CDlist Cdlist_intersecar_custom(CDlist lista1, CDlist lista2, FuncionComparadora comp) {

}

CDlist Cdlist_ordenar(CDlist *lista, FuncionComparadora comp) {
}

CDlist Cdlist_reverso(CDlist *lista){
}

CDlist Cdlist_intercalar(CDlist lista1, CDlist lista2) {
}

CDlist Cdlist_partir(CDlist *lista) {
}