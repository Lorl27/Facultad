// 2. Implemente pilas generales utilizando las listas simplemente enlazadas generales de la pr´actica 2.
// Utilice la siguiente declaraci´on:
// 
// Defina las mismas operaciones que en el ejercicio anterior, ajustando los prototipos seg´un lo requiera.
// Procure manipular la lista ´unicamente a trav´es de las funciones declaradas en su interfaz.

#include "glist.h"
#include <stdio.h>
#include <stdlib.h>


typedef GList Pila;

// i. Pila pila crear(int): crea e inicializa una nueva pila vac´ıa con la capacidad dada.
Pila pila_crear(){
    return NULL;
}

// ii. void pila destruir(Pila): libera la memoria requerida para la pila.
void pila_destruir(Pila pila, FuncionDestructora destroy){
    if(pila==NULL || pila->data==NULL) return;

    glist_destruir(pila->data, destroy);
    free(pila);
}

// iii. int pila es vacia(Pila): retorna 1 si la pila est´a vac´ıa, y 0 en caso contrario.
int pila_es_vacia(Pila pila){
    return pila == NULL || glist_vacia(pila->data);

}

// iv. int pila tope(Pila): retorna el elemento que se encuentre en el tope de la pila, pero sin
// eliminarlo.
int pila_tope(Pila pila){
    if(pila_es_vacia(pila)) exit(EXIT_FAILURE);

    if(pila->next==NULL) return *(int* )pila->data;

    return pila_tope(pila->next);
}

// v. void pila apilar(Pila, int): inserta un elemento en el tope de la pila, en caso que la pila
// se encuentre llena, deber´a aumentar al doble la capacidad del arreglo.
// Ayuda: puede llamar a la funci´on arreglo enteros ajustar.

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

// vi. void pila desapilar(Pila): elimina el elemento que se encuentra en el tope de la pila.
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

void pila_Desapilar_recursiva(Pila *pila, FuncionDestructora destroy){
    if(pila_es_vacia(*pila)) return;

    GList tmp=*pila;

    if(tmp->next==NULL){
        destroy(tmp->data);
        free(tmp);
        *pila=NULL;
        return;
    }

    pila_Desapilar_recursiva(&(tmp->next),destroy);
}

// vii. void pila imprimir(Pila): imprime en orden los elementos de la pila.
void pila_imprimir(Pila pila){
    if(pila_es_vacia(pila)){
        printf("Esta vacia...\n");
        return;
    }
    
    for(GNode *tmp=pila;tmp!=NULL;tmp=tmp->next){
        printf("%d\n",*(int*)tmp->data);
    }

}


void* copiar_entero(void* dato) {
    int* nuevo = malloc(sizeof(int));
    *nuevo = *(int*)dato;
    return nuevo;
}

void destruir_entero(void* dato) {
    free(dato);
}


//extra: visual
void pila_apilar2(Pila *pila, void *elemento, FuncionCopia c) {
    if (c == NULL) return;

    GNode *nuevo = malloc(sizeof(GNode));
    if (!nuevo) return;

    nuevo->data = c(elemento);
    nuevo->next = *pila;
    *pila = nuevo;
}

void pila_desapilar2(Pila *pila, FuncionDestructora destroy) {
    if (pila_es_vacia(*pila)) return;

    GNode *tmp = *pila;
    *pila = tmp->next;
    destroy(tmp->data);
    free(tmp);
}

int pila_tope2(Pila pila) {
    if (pila_es_vacia(pila)) exit(EXIT_FAILURE);
    return *(int*)pila->data;
}





int main() {
    Pila pila = pila_crear();
    pila_imprimir(pila);

    int a = 10, b = 20, c = 30, d = 40;

    printf("Apilando elementos...\n");
    pila_apilar(&pila, &a, copiar_entero);
    //pila_imprimir(pila);

    pila_apilar(&pila, &b, copiar_entero);
    //pila_imprimir(pila);

    pila_apilar(&pila, &c, copiar_entero);
    //pila_imprimir(pila);

    printf("Apilando un elemento más...\n");
    pila_apilar(&pila, &d, copiar_entero);
    pila_imprimir(pila);

    printf("Tope de la pila: %d\n", pila_tope(pila));

    printf("Desapilando un elemento...\n");
    pila_desapilar(&pila, destruir_entero);
    //pila_imprimir(pila);

    printf("Desapilando otro elemento...\n");
    pila_desapilar(&pila, destruir_entero);
    //pila_imprimir(pila);

    printf("Desapilando el último elemento...\n");
    pila_desapilar(&pila, destruir_entero);
    pila_imprimir(pila);

    printf("Desapilando de una pila vacía...\n");
    pila_desapilar(&pila, destruir_entero);
    pila_imprimir(pila);

    pila_destruir(pila, destruir_entero);
    return 0;
}
