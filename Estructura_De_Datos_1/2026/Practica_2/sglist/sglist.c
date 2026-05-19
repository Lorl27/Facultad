#include <stdio.h>
#include <stdlib.h>
#include "sglist.h"


SGList sglist_crear(){
    return NULL;
}

void sglist_destruir(SGList lista, FuncionDestructora destroy){
    if(!lista) return;    
    GNode * tmp=lista;
    GNode * e;
    while(tmp!=NULL){
        e=tmp;
        tmp=tmp->next;
        destroy(e->data);
        free(e);
    }
    destroy(lista->data);
    free(lista);
}


int sglist_vacia(SGList lista){
    return lista==NULL;
}


void sglist_recorrer(SGList lista, FuncionVisitante visit){
    for(GNode * tmp =lista; tmp!=NULL;tmp=tmp->next){
        visit(tmp->data);
    }
}


SGList sglist_insertar(SGList lista, void * dato, FuncionCopia copy, FuncionComparadora comp){
    GNode *nuevo = malloc(sizeof(GNode));
    nuevo->data = copy(dato);

    //Caso Base: Lista vacía o el nuevo es MENOR que la cabeza actual
    // comp() retorna > 0 si lista->data es mayor que dato
    if (lista == NULL || comp(lista->data, dato) > 0) {
        nuevo->next = lista;
        return nuevo; // Nueva cabeza
    }

    GNode *anterior = lista;
    GNode *actual = lista->next;

    // Caminamos MIENTRAS el 'actual' sea MENOR o IGUAL al 'dato'
    while (actual != NULL && comp(actual->data, dato) <= 0) {
        anterior = actual;
        actual = actual->next;
    }

    nuevo->next = actual;
    anterior->next = nuevo;

    return lista;
}

int sglist_buscar(GList lista, void *dato, FuncionComparadora comp) {
    for (GNode *tmp = lista; tmp != NULL; tmp = tmp->next) {
        int comparacion = comp(tmp->data, dato);
        
        if (comparacion == 0) {
            return 1; 
        }
        
        if (comparacion > 0) {
            // El dato actual de la lista es MAYOR al que buscamos.
            // Como la lista está ordenada, es imposible que esté más adelante.
            return 0; // Cortamos la búsqueda temprano
        }
    }
    return 0; 
}

GList sglist_arr(void **array, int long_array, FuncionCopia copy, FuncionComparadora comp) {
    SGList lista = sglist_crear(); // Empezamos con lista vacía
    
    for (int i = 0; i < long_array; i++) {
        // Vamos insertando cada elemento. ¡La función se encarga de ordenarlos!
        lista = sglist_insertar(lista, array[i], copy, comp);
    }
    
    return lista;
}