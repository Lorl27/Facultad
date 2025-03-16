// 3. Arrays
// Ejercicio 9. Escriba un programa que complete un arreglo con los primeros 100 números
// enteros a partir del 0 y los muestre en pantalla en orden ascendente.

#include <stdio.h>


void completar_array(int *arreglo){
    for(int x=0;x<100;x++){
        arreglo[x]=x;
    }
}

void imprimir_array(int arreglo[]){
    for(int x=0;x<100;x++){
        printf("%d \n",arreglo[x]);}
}

int main(void){
    int array[100];
    completar_array(array);
    imprimir_array(array);

    return 0;
}