#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

// Función de copia para enteros
void * copiarEntero(void * dato) {
    int * nuevo = malloc(sizeof(int));
    *nuevo = *(int *)dato;
    return nuevo;
}

// Función destructora para enteros
void destruirEntero(void * dato) {
    free(dato);
}

int main() {
    // Crear pila
    Pila p = pila_crear();

    // Verificar si está vacía
    printf("¿La pila está vacía? %s\n", isEmpty(p) ? "Sí" : "No");

    // Insertar elementos
    int a = 10, b = 20, c = 30;
    Push(p, &a, copiarEntero);
    Push(p, &b, copiarEntero);
    Push(p, &c, copiarEntero);

    // Verificar si está vacía
    printf("¿La pila está vacía? %s\n", isEmpty(p) ? "Sí" : "No");

    // Mostrar el tope
    int * tope = (int *)Top(p);
    printf("Elemento en el tope: %d\n", *tope);

    // Eliminar un elemento
    p = Pop(p, destruirEntero);
    tope = (int *)Top(p);
    printf("Nuevo tope tras Pop: %d\n", *tope);

    // Destruir toda la pila
    p=pila_destruir(p, destruirEntero);

    printf("¿La pila está vacía al final? %s\n", isEmpty(p) ? "Sí" : "No");

    return 0;
}
