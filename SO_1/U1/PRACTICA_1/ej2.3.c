
//  c) Si un le descriptor se duplica con dup() que pasa al cerrar una de las copias?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char cadena[100];
    int numero;

    // Duplicamos stdin
    int new_stdin = dup(0);
    printf("Duplicamos stdin. Descriptor duplicado: %d\n", new_stdin);

    // Cerramos el descriptor original de stdin
    close(0);
    printf("Cerramos stdin original (0).\n");

    // Probamos si el nuevo descriptor sigue funcionando
    printf("Ingrese un número: \n");
    if (scanf("%i", &numero) == EOF) {
        printf("Error: No se puede leer de stdin porque está cerrado.\n");
    } else {
        printf("Se recibió el número %d\n", numero);
    }

    // Ahora cerramos también el descriptor duplicado
    close(new_stdin);
    printf("Cerramos el descriptor duplicado.\n");

    // Intentamos leer de nuevo (debería fallar)
    printf("Ingrese una cadena: \n");
    if (fgets(cadena, 100, stdin) == NULL) {
        printf("Error: No se puede leer de stdin.\n");
    } else {
        printf("¿La cadena se imprimió?: %s\n", cadena);
    }

    return 0;
}


//* * A pesar de hacer duplicado y solo cerrar una de las copias, se siguen cerrando las 2.
// * A MENOS que lo re-deriga al stdin:
// 
// 
// 
// 


int main_2() {
    char cadena[100];
    int numero;

    // Duplicamos stdin y forzamos que el nuevo descriptor se llame 3
    int new_stdin = dup(0);
    printf("Duplicamos stdin. Descriptor duplicado: %d\n", new_stdin);

    // Cerramos stdin original (descriptor 0)
    close(0);
    printf("Cerramos stdin original (0).\n");

    // Redirigimos el descriptor duplicado para que sea stdin otra vez
    dup2(new_stdin, 0);
    printf("Redirigimos el descriptor duplicado a stdin.\n");

    // Ahora probamos leer de nuevo
    printf("Ingrese un número: \n");
    if (scanf("%i", &numero) == EOF) {
        printf("Error: No se puede leer de stdin porque está cerrado.\n");
    } else {
        printf("Se recibió el número %d\n", numero);
    }

    // Cerramos el descriptor duplicado
    close(new_stdin);
    printf("Cerramos el descriptor duplicado.\n");

    // Intentamos leer de nuevo (debería fallar)
    printf("Ingrese una cadena: \n");
    if (fgets(cadena, 100, stdin) == NULL) {
        printf("Error: No se puede leer de stdin.\n");
    } else {
        printf("¿La cadena se imprimió?: %s\n", cadena);
    }

    return 0;
}
