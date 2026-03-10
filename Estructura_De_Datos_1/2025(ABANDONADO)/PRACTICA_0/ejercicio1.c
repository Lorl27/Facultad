//? Gesti´on de la memoria y punteros

// 1:  Escriba un programa que declare algunas variables locales, e imprima las direcciones de memoria de
// las mismas. Pruebe declarar un arreglo de caracteres, y verifique que las direcciones de sus elementos
// son contiguas.

#include <stdio.h>
#include <stdlib.h>

int main(){
    int a=5,b=2;

    printf("La dirección de a es: %d y la de b: %d \n",&a,&b);

    char arreglo[2];

    printf("La direccion del array es: %d", &arreglo);

    return 0;
}