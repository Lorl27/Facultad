#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "Heap.h"

void * no_copiar(void * a){
    return a;
}

int comparar_puntero_entero(void * a, void * b){
    int a_e=*(int *)a;
    int b_e=*(int*)b;
    if(a_e>b_e) return 1;
    if(a_e<b_e) return -1;
    return 0;
}

void no_destruir(void *){

}


int main() {
    int N = 10000;
    void ** arreglo_desordenado = malloc(sizeof(void *) * N);
    
    // Generar 10.000 números aleatorios
    srand(time(NULL));
    for(int i = 0; i < N; i++) {
        int * num = malloc(sizeof(int));
        *num = rand() % 100000; // Números aleatorios
        arreglo_desordenado[i] = num;
    }

    
    BHeap heap = bheap_crear_desde_arr(arreglo_desordenado, N, no_copiar, comparar_puntero_entero);

    // Arreglo para guardar el resultado ordenado
    int * arreglo_ordenado = malloc(sizeof(int) * N);

    // 2. Extraer siempre el máximo hasta vaciar el heap
    // Los iremos guardando desde el final (N-1) hacia adelante (0) 
    // para que queden en orden CRECIENTE (de menor a mayor)
    for(int i = N - 1; i >= 0; i--) {
        // Sacamos el máximo de la raíz
        int max_actual = *(int*)(heap->arr[1]);
        arreglo_ordenado[i] = max_actual;
        
        // Lo eliminamos del heap (achicando la estructura y hundiendo la nueva raíz)
        heap = bheap_eliminar_maximo(heap, comparar_puntero_entero, no_destruir);
    }

    // Comprobación (imprimir los primeros 10 y los últimos 10)
    printf("Primeros 10: ");
    for(int i=0; i<10; i++) printf("%d ", arreglo_ordenado[i]);
    
    printf("\nUltimos 10: ");
    for(int i=N-10; i<N; i++) printf("%d ", arreglo_ordenado[i]);

    //  liberar memoria de los mallocs...
    // A) Liberar cada uno de los 10.000 punteros a enteros que creamos en el primer for
    for(int i = 0; i < N; i++) {
        free(arreglo_desordenado[i]); 
    }
    
    // B) Liberar el arreglo dinámico que los contenía
    free(arreglo_desordenado);
    
    // C) Liberar el arreglo de resultados
    free(arreglo_ordenado);
    
    // D) Liberar la estructura interna del Heap (su arreglo propio y el struct)
    bheap_destruir(heap, no_destruir);
    
    printf("\n[ Memoria liberada correctamente ]\n");
    
    return 0;
}