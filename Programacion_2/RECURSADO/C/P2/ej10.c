// Ejercicio 10. Escriba un programa que complete un arreglo con los números pares que se
// encuentren entre 100 y 200 y los muestre en pantalla en orden descendente.

#include <stdio.h>

void completar_array(int *arreglo){
    int index=0;
    for(int x=100;x<=200;x++){
        if(x%2==0){
            arreglo[index]=x;
            index++;
        }
    }
}

void imprimir_array(int *array){
    for(int x=51;x>=0;x--){
        if(x%2==0){
            printf("En el lugar nro %d, se encuentra: %d \n", x, array[x]);
        }
    }
}

int main(void){
    int arreglo[51];

    completar_array(arreglo);
    imprimir_array(arreglo);

    return 0;
}