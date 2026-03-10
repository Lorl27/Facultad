//? PILAS Y COLAS

// 1. Implemente pilas utilizando los arreglos din´amicos de n´umeros enteros de la pr´actica 1.

// a) Escriba un archivo cabecera de nombre arregloenteros.h con las declaraciones a exportar para
// manipular de manera externa los arreglos din´amicos

// b) Considere la siguiente definici´on de pilas que guarda un puntero a un arreglo din´amico y un entero
// con la ´ultima posici´on ocupada del arreglo:


// c) Defina las siguientes operaciones b´asicas de pilas. Procure manipular el arreglo din´amico ´unicamente
// a trav´es de las funciones declaradas en su interfaz.

#include "arregloEnteros.h"

#include <stdio.h>
#include <stdlib.h>

struct _Pila {
    ArregloEnteros *arr;
    int ultimo; // índice!!!! del último elemento ocupado
};

typedef struct _Pila *Pila;

// i. Pila pila crear(int): crea e inicializa una nueva pila vac´ıa con la capacidad dada.
Pila pila_crear(int capacidad){
    ArregloEnteros *arreglo=arreglo_enteros_crear(capacidad);
    Pila pila=malloc(sizeof(struct _Pila));
    pila->arr = arreglo;
    pila->ultimo=0; //sin datos.

    return pila;
}

// ii. void pila destruir(Pila): libera la memoria requerida para la pila.
void pila_destruir(Pila pila){
    if(pila==NULL || pila->arr==NULL) return;

    arreglo_enteros_destruir(pila->arr);
    free(pila);

}

// iii. int pila es vacia(Pila): retorna 1 si la pila est´a vac´ıa, y 0 en caso contrario.
int pila_es_vacia(Pila pila){
    return pila==NULL || pila->ultimo==0;
}

// iv. int pila tope(Pila): retorna el elemento que se encuentre en el tope de la pila, pero sin
// eliminarlo.
int pila_tope(Pila pila){
    if(pila->ultimo==0) return -1;

    return arreglo_enteros_leer(pila->arr,pila->ultimo - 1);
}

// v. void pila apilar(Pila, int): inserta un elemento en el tope de la pila, en caso que la pila
// se encuentre llena, deber´a aumentar al doble la capacidad del arreglo.
// Ayuda: puede llamar a la funci´on arreglo enteros ajustar.

void pila_apilar(Pila pila, int elemento){
    
    int capacidad_Array=pila->arr->capacidad;
    if(pila->ultimo == capacidad_Array){
        capacidad_Array*=2;
        arreglo_enteros_ajustar(pila->arr,capacidad_Array);
    }

    
    arreglo_enteros_insertar(pila->arr,pila->ultimo,elemento);
    pila->ultimo++;
}

// vi. void pila desapilar(Pila): elimina el elemento que se encuentra en el tope de la pila.
void pila_desapilar(Pila pila){
    if(pila_es_vacia(pila)) return;

    arreglo_enteros_eliminar(pila->arr,pila->ultimo-1);
    pila->ultimo--;

    
}

// vii. void pila imprimir(Pila): imprime en orden los elementos de la pila.
void pila_imprimir(Pila pila){
    if (pila_es_vacia(pila)) {
        printf("Pila vacía\n");
        return;
    }


    printf("[");
    for (int i = 0; i < pila->ultimo; i++) { // Solo iteramos hasta "ultimo"
        printf("%d", arreglo_enteros_leer(pila->arr, i));
        if (i < pila->ultimo - 1) {
            printf(", ");
        }
    }
    printf("]\n");

}


int main() {
    // Crear una pila con capacidad inicial de 3
    Pila pila = pila_crear(3);
    pila_imprimir(pila);

    // Apilar elementos
    printf("Apilando elementos...\n");
    pila_apilar(pila, 10);
        pila_imprimir(pila);

    pila_apilar(pila, 20);
        pila_imprimir(pila);

    pila_apilar(pila, 30);
        


    // Imprimir la pila
    printf("Pila después de apilar 10, 20, 30:\n");
    pila_imprimir(pila);

    // Apilar un elemento más para probar si se ajusta la capacidad
    printf("Apilando un elemento más...\n");
    pila_apilar(pila, 40);
    pila_imprimir(pila); // Verificar que la capacidad se haya duplicado

    // Ver el tope de la pila
    printf("Tope de la pila: %d\n", pila_tope(pila));

    // Desapilar un elemento
    printf("Desapilando un elemento...\n");
    pila_desapilar(pila);
    pila_imprimir(pila);

    // Desapilar otro elemento
    printf("Desapilando otro elemento...\n");
    pila_desapilar(pila);
    pila_imprimir(pila);

    // Desapilar el último elemento
    printf("Desapilando el último elemento...\n");
    pila_desapilar(pila);
    pila_imprimir(pila);

    // Intentar desapilar de una pila vacía
    printf("Desapilando de una pila vacía...\n");
    pila_desapilar(pila);
    pila_imprimir(pila); // Debería seguir vacía

    // Destruir la pila
    pila_destruir(pila);

    return 0;
}