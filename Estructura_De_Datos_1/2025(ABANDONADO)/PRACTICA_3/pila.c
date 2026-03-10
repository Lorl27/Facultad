#include "pila.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

Pila pila_crear(){
    return NULL;
}

void pila_destruir(Pila pila, FuncionDestructora destroy){
    if(pila==NULL || pila->data==NULL) return;

    glist_destruir(pila->data, destroy);
    free(pila);
}

int pila_es_vacia(Pila pila){
    return pila == NULL || glist_vacia(pila->data);

}

int pila_tope(Pila pila){
    if(pila_es_vacia(pila)) exit(EXIT_FAILURE);

    if(pila->next==NULL) return *(int* )pila->data;

    return pila_tope(pila->next);
}

GList sglist_agregar_final(GList list, void *data, FuncionCopia copy){
    GNode *nuevoNodo=malloc(sizeof(GNode));
    if(nuevoNodo==NULL) return NULL;
    nuevoNodo->next=NULL;
    nuevoNodo->data=copy(data);

    if(sglist_vacia(list)){ 
        return nuevoNodo;
        }
    else{
        GNode *actual=list;
        while(actual->next!=NULL){  
            actual=actual->next;  //tenemos que recorrer TODA la lista
        }
        actual->next=nuevoNodo;  //ya llegamos al final, entonces lo ponermos :)
        return list;
    }

}

void pila_apilar(Pila *pila, void *elemento,FuncionCopia c){
    if( c==NULL) return;
    
    *pila=sglist_agregar_final(*pila,elemento,c);

}

void pila_desapilar(Pila *pila, FuncionDestructora destroy){
    if(pila_es_vacia(*pila)) return;

    GNode *inicio=*pila;
    GNode *final=NULL;

    while(inicio->next!=NULL){
        final=inicio;
        inicio=inicio->next;
    }

    if(final==NULL){
        destroy(inicio->data);
        free(inicio);
        *pila=NULL;
    }else{
        final->next=NULL;
        destroy(inicio->data);
        free(inicio);
    }
    
}

void pila_imprimir(Pila pila){
    if(pila_es_vacia(pila)){
        printf("Esta vacia...\n");
        return;
    }
    
    for(GNode *tmp=pila;tmp!=NULL;tmp=tmp->next){
        printf("%d\n",*(int*)tmp->data);
    }

}
