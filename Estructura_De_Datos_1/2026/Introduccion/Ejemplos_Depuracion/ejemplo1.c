#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Iniciando el programa...\n");

    // Pedimos memoria dinámica para 3 enteros en el Heap
    int *arreglo = malloc(3 * sizeof(int));

    arreglo[0] = 10;
    arreglo[1] = 20;
    arreglo[2] = 30;

    // ERROR 1: Escribimos en la posición 4 (índice 3), la cual NO nos pertenece.
    arreglo[3] = 40; 
    
    printf("El valor invasor es: %d\n", arreglo[3]);

    // ERROR 2: ¡Fuga de memoria! Termina el programa pero nunca hicimos free(arreglo);

    return 0;
}