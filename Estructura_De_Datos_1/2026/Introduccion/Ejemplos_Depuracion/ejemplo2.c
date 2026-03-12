#include <stdio.h>

int main() {
    printf("Preparando el desastre...\n");

    // Creamos un puntero y explícitamente le decimos que no apunte a nada (NULL)
    int *puntero_peligroso = NULL;

    printf("A punto de colapsar en 3, 2, 1...\n");

    // ¡BAM! Intentamos guardar el número 42 en la dirección de memoria 0.
    // El sistema operativo prohíbe tocar esta dirección.
    *puntero_peligroso = 42; 

    printf("Esta línea nunca se va a imprimir en la pantalla.\n");

    return 0;
}