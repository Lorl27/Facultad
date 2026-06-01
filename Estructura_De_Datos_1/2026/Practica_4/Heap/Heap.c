#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

BHeap bheap_crear(int capacidad){
    BHeap  heap = malloc(sizeof(struct _BHeap));
    if(heap!=NULL){
        heap->capacidad=capacidad;
        heap->arr=malloc(sizeof(void * )*capacidad);
        heap->ultimo=0; //ninguno ocupado
    }
    return heap;
}

int bheap_es_vacio(BHeap heap){
    return heap==NULL || heap->ultimo==0;
}

void bheap_destruir(BHeap heap,FuncionDestructora destroy){
    if(heap==NULL) return;

    for(int x=1;x<=heap->ultimo;x++){
        destroy(heap->arr[x]);
    }
    free(heap->arr);
    free(heap);
}


void bheap_recorrer(BHeap heap, FuncionVisitante visit){
    if(bheap_es_vacio(heap)) return;

    for(int x=1; x<=heap->ultimo;x++) visit(heap->arr[x]);
}


// Función auxiliar (El "Sift-Up" o "Trepar")
void bheap_subir(BHeap heap, int pos, FuncionComparadora comp) {
    // Mientras no seamos la raíz y seamos MAYORES que nuestro padre, trepamos
    while (pos > 1 && comp(heap->arr[pos], heap->arr[pos/2]) > 0) {
        void * temp = heap->arr[pos];
        heap->arr[pos] = heap->arr[pos/2];
        heap->arr[pos/2] = temp;
        
        pos = pos / 2; // Actualizamos la posición para seguir subiendo
    }
}


BHeap bheap_insertar(BHeap heap, void * elemento, FuncionCopiadora copy, FuncionComparadora comp){
    if(heap==NULL) return heap;

    // ¿El arreglo está lleno? 
    if(heap->ultimo == heap->capacidad - 1){
        heap->capacidad *= 2; // Duplicamos capacidad
        heap->arr = realloc(heap->arr, sizeof(void *) * heap->capacidad);
    }

    heap->ultimo++;
    heap->arr[heap->ultimo]=copy(elemento);

   bheap_subir(heap, heap->ultimo, comp);

    return heap;
}

// Función auxiliar (El "Sift-Down" o "Hundimiento")
void bheap_hundir(BHeap heap, int pos, FuncionComparadora comp) {
    int es_mayor = 1;
    while(2 * pos <= heap->ultimo && es_mayor) {
        int k = 2 * pos; // Hijo izquierdo
        
        // Si hay derecho y es mayor que el izquierdo, apuntamos al derecho
        if(k + 1 <= heap->ultimo && comp(heap->arr[k+1], heap->arr[k]) > 0) {
            k = k + 1;
        }

        // Si soy menor que mi hijo mayor, me hundo
        if(comp(heap->arr[pos], heap->arr[k]) < 0) {
            void * temp = heap->arr[pos];
            heap->arr[pos] = heap->arr[k];
            heap->arr[k] = temp;
            pos = k; // Sigo bajando
        } else {
            es_mayor = 0; // Si soy mayor, ya estoy bien ubicado
        }
    }
}

BHeap bheap_eliminar_maximo(BHeap heap, FuncionComparadora comp, FuncionDestructora destroy){
    if(bheap_es_vacio(heap)) return heap;

    // 1. Destruimos el máximo (la raíz)
    destroy(heap->arr[1]);

    // 2. Agarramos al último y lo ponemos en la raíz. Achicamos el Heap.
    heap->arr[1] = heap->arr[heap->ultimo];
    heap->ultimo--;

    bheap_hundir(heap, 1, comp);

    return heap;
}


BHeap bheap_eliminar_elemento(BHeap heap, void * elemento, FuncionComparadora comp, FuncionDestructora destroy){
    if(bheap_es_vacio(heap)) return heap;

    int pos_a_borrar = -1;

    // 1. Buscar el elemento (O(n) porque el Heap no está ordenado como un ABB)
    for(int i = 1; i <= heap->ultimo; i++){
        if(comp(heap->arr[i], elemento) == 0){
            pos_a_borrar = i;
            break;
        }
    }

    // Si no estaba en el heap, no hacemos nada
    if(pos_a_borrar == -1) return heap;

    // 2. Destruimos el dato
    destroy(heap->arr[pos_a_borrar]);

    // 3. Movemos el ÚLTIMO elemento a la posición vacía y achicamos
    heap->arr[pos_a_borrar] = heap->arr[heap->ultimo];
    heap->ultimo--;

    // Si borramos justo el que ya estaba al final, no hay que reordenar
    if(pos_a_borrar > heap->ultimo) return heap;

    // 4. REORDENAR EL INFILTRADO (Puede subir o puede bajar)
    int pos = pos_a_borrar;

    // Opción A: ¿Debe TREPAR? (Si es mayor que su padre)
    if (pos > 1 && comp(heap->arr[pos], heap->arr[pos/2]) > 0) {
        bheap_subir(heap, pos, comp);
    } 
    // Opción B: Si no trepó, ¿Debe HUNDIRSE? (Si es menor que sus hijos)
    else { 
        bheap_hundir(heap, pos, comp);
    }

    return heap;

}







BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copiar,FuncionComparadora comp){
    // Pedimos capacidad + 1 porque en los Heaps ignoramos el índice 0
    BHeap heap = bheap_crear(largo + 1); 
    
    if(largo == 0 || arr == NULL) return heap;

    // 1. Copiamos los datos "a lo bruto" (queda un árbol desordenado)
    for(int i = 0; i < largo; i++) {
        heap->arr[i + 1] = copiar(arr[i]);
    }
    heap->ultimo = largo;

    // 2. Aplicamos la Magia (Heapify en O(n)):
    // Empezamos desde el último padre (ultimo / 2) hasta la raíz (1) y los hundimos.
    for(int i = heap->ultimo / 2; i >= 1; i--) {
        bheap_hundir(heap, i, comp);
    }

    return heap;
}

