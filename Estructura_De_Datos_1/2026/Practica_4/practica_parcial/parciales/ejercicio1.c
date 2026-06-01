#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP 20

// --- Estructuras dadas en el examen ---
typedef struct {
    char *dni, *nombre, *descripcionCargo;
    int prioridad;
} Invitado; // Nota: Aquí Invitado NO es puntero, es la estructura por valor

typedef struct _Nodo {
    Invitado invitado;
    struct _Nodo *der, *izq; // Ojo, los profes los pusieron al revés (der, izq)
} Nodo;

typedef Nodo* Arbol;

typedef struct {
    Invitado datos[MAX_HEAP];
    int nelems;
} _BHeap;

typedef _BHeap* BHeap;


// ---------------------------------------------------------
// PARTE A: DE HEAP (ARREGLO) A ÁRBOL BINARIO
// ---------------------------------------------------------

// Función auxiliar para armar el árbol recursivamente usando los índices
Arbol heap_a_arbol_aux(Invitado datos[], int n, int indice_actual) {
    // Si el índice se sale de la cantidad de elementos, no hay nodo acá
    if (indice_actual >= n) return NULL;

    Arbol nuevo = malloc(sizeof(Nodo));
    nuevo->invitado = datos[indice_actual]; // Copia por valor
    
    // Magia de Heaps: 
    // Izquierdo = 2*i + 1
    // Derecho   = 2*i + 2
    nuevo->izq = heap_a_arbol_aux(datos, n, 2 * indice_actual + 1);
    nuevo->der = heap_a_arbol_aux(datos, n, 2 * indice_actual + 2);
    
    return nuevo;
}

Arbol convierteHeapEnArbol(BHeap bHeap) {
    if (bHeap == NULL || bHeap->nelems == 0) return NULL;
    
    // Arrancamos desde la raíz (índice 0)
    return heap_a_arbol_aux(bHeap->datos, bHeap->nelems, 0);
}


// ---------------------------------------------------------
// PARTE B: DE ÁRBOL BINARIO A HEAP (ARREGLO)
// ---------------------------------------------------------

// Función auxiliar recursiva
// El enunciado nos regala la mejor pista: "Asumir que el árbol es COMPLETO".
// Gracias a esto, no necesitamos hacer un recorrido BFS (por niveles) con Cola.
// Podemos usar la misma matemática de índices pero al revés.
void arbol_a_heap_aux(Arbol arbol, BHeap heap, int indice_actual) {
    if (arbol == NULL) return;

    // Guardamos el dato en la posición calculada
    heap->datos[indice_actual] = arbol->invitado;
    
    // Actualizamos la cantidad de elementos si llegamos más lejos
    if (indice_actual >= heap->nelems) {
        heap->nelems = indice_actual + 1;
    }

    // Mandamos a los hijos a sus respectivas posiciones matemáticas
    arbol_a_heap_aux(arbol->izq, heap, 2 * indice_actual + 1);
    arbol_a_heap_aux(arbol->der, heap, 2 * indice_actual + 2);
}

BHeap convierteArbolEnHeap(Arbol inicio) {
    if (inicio == NULL) return NULL;
    
    BHeap nuevo_heap = malloc(sizeof(_BHeap));
    nuevo_heap->nelems = 0;
    
    arbol_a_heap_aux(inicio, nuevo_heap, 0);
    
    return nuevo_heap;
}