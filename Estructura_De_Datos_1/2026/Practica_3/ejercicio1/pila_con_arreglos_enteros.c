#include <stdio.h>
#include <stdlib.h>
#include "pila_con_arreglos_enteros.h"

Pila pila_crear(int capacidad){
    Pila pila=malloc(sizeof(struct _Pila));
    if (pila!=NULL){
        pila->arr=arreglo_enteros_crear(capacidad);
        pila->ultimo=-1;
    }
    return pila;
}

int pila_es_vacia(Pila pila){
    return (pila==NULL || pila->ultimo==-1);
}

void pila_destruir(Pila pila){
    if(pila == NULL) return;
    arreglo_enteros_destruir(pila->arr);
    free(pila);
}


int pila_tope(Pila pila){
    return arreglo_enteros_leer(pila->arr,pila->ultimo);
}

// void pila_apilar(Pila pila, int elemento){
//     arreglo_enteros_insertar(pila->arr,0,elemento);
// }

// void pila_desapilar(Pila pila){
//     if(pila_es_vacia(pila)) return;
//     arreglo_enteros_eliminar(pila->arr,0);
// }


void pila_apilar(Pila pila, int elemento){
    if (pila == NULL) return;

    // 1. Verificamos si estamos al límite de la capacidad
    // Como los índices empiezan en 0, si ultimo es 4 y la capacidad es 5, ¡está llena!
    if (pila->ultimo + 1 == arreglo_enteros_capacidad(pila->arr)) {
        int nueva_cap = arreglo_enteros_capacidad(pila->arr) * 2;
        // Si estaba en 0, la forzamos a crecer
        if (nueva_cap == 0) nueva_cap = 2; 
        
        arreglo_enteros_ajustar(pila->arr, nueva_cap);
    }

    // 2. Incrementamos el tope
    pila->ultimo++;

    // 3. Escribimos el dato exactamente en ese nuevo hueco
    // ¡Es O(1)! No hay mudanzas.
    arreglo_enteros_escribir(pila->arr, pila->ultimo, elemento);
}

void pila_desapilar(Pila pila){
    if(pila_es_vacia(pila)) return;

    // ¡MAGIA PURA!
    // Para desapilar en un arreglo, NO hace falta borrar el dato ni mudar nada.
    // Simplemente "bajamos" el índice del tope. 
    // Ese dato quedará ahí como "basura", pero será sobreescrito en el próximo 'apilar'.
    pila->ultimo--;
}

void pila_imprimir(Pila pila){
    if(pila_es_vacia(pila)) {
        printf("Pila vacia\n");
        return;
    }
    
    // Como es una pila, conceptualmente se imprime desde el tope hacia la base
    printf("Tope -> ");
    for(int i = pila->ultimo; i >= 0; i--){
        int val = arreglo_enteros_leer(pila->arr, i);
        printf("[%d] ", val);
    }
    printf("<- Base\n");
}
