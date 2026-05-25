//3. Escriba una funci´on que utilice una pila para revertir el orden de una lista simplemente enlazada.

#include "../Practica_3/Pila/pila.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/slist/slist.h"

//sup son enteros los datos de la lista simplemente enlazada
int * copiar_enteros(int * entero){
    int * copia=malloc(sizeof(int));
    *copia=*entero;
    return copia;
}

void destruir_enteros(int * entero){
    free(entero);
}


SList Revertir_orden( SList lista){
    if (lista == NULL) return NULL;

    SList  nueva=slist_crear();
    Pila pila=pila_crear();
    SNodo *tmp = lista;

    while(tmp!=NULL){
        pila=Push(pila,&tmp->dato,(FuncionCopia)copiar_enteros);
        tmp=tmp->sig;
    }

    while(!isEmpty(pila)){
        int tope= * (int *) Top(pila);
        nueva=slist_agregar_final(nueva,tope);
        pila=Pop(pila,destruir_enteros);
    }

    pila=pila_destruir(pila,destruir_enteros);
    return nueva;
    
}



// version usando la misma lista:
SList Revertir_orden_optimo(SList lista){
    if (lista == NULL) return NULL;
    
    Pila pila = pila_crear();
    SNodo *tmp = lista;

    while(tmp != NULL){
        pila = Push(pila, &(tmp->dato), (FuncionCopia)copiar_enteros);
        tmp = tmp->sig;
    }

    // Volvemos a recorrer la MISMA lista desde el principio
    tmp = lista;
    while(!isEmpty(pila)){
        // Sobreescribimos el dato viejo con el que sale de la pila
        tmp->dato = *(int*)Top(pila); 
        
        pila = Pop(pila, destruir_enteros);
        tmp = tmp->sig;
    }

    pila_destruir(pila, destruir_enteros);
    return lista; // Devolvemos la misma lista, pero con sus datos invertidos
}
