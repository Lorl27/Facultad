// 3. Escriba una funci´on que utilice una pila para revertir el orden de una lista simplemente enlazada.

#include "glist.h"
#include "slist.h"
#include "pila.h"

#include <stdio.h>
#include <stdlib.h>


typedef GList Pila;

//yo quiero usar top para marcar el último
void revertir_orden(SList *lista, FuncionCopia c,FuncionDestructora f){
    SNodo *actual=*lista;

    Pila pila=pila_crear();

    //apilamos los datos
    while(actual!=NULL){
        pila_apilar(&pila,&actual->dato,c);
        actual=actual->sig;
    }

    actual=*lista;

    //los desapilamos y reescribimos
    while(actual!=NULL){
        actual->dato=pila_tope(pila);
        pila_desapilar(&pila,f);
        actual=actual->sig;
    }

    
   pila_destruir(pila,f);

}


//-----------
void *copia_entero(void *dato) {
    int *nuevo = malloc(sizeof(int));
    *nuevo = *(int *)dato;
    return nuevo;
}

void destruir_entero(void *dato) {
    free(dato);
}

void imprimir(int dato){
    printf("%d \t",dato);
}

int main() {
    SList lista = NULL;

    // Cargamos la lista: 3 -> 2 -> 1
    lista = slist_agregar_inicio(lista, 1);
    lista = slist_agregar_inicio(lista, 2);
    lista = slist_agregar_inicio(lista, 3);

    printf("Lista original:\n");
    slist_recorrer(lista,imprimir); // Debería imprimir: 3 2 1

    revertir_orden(&lista,copia_entero,destruir_entero);

    printf("\nLista invertida:\n");
    slist_recorrer(lista,imprimir); // Debería imprimir: 1 2 3

    return 0;
}
