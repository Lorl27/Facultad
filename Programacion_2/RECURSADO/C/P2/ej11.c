// Ejercicio 11. Escriba un programa que complete un arreglo con los primeros 50 múltiplos de
// 3 y los muestre en pantalla en orden descendente.

#include <stdio.h>


void completar_array(int *arreglo){
    int index=0;
    for(int x =3;index<50;x+=3){
            arreglo[index]=x;
            index++;
        }
}

void imprimir_array(int *arreglo, int tam){
    for(int x=tam-1;x>=0;x--){
        printf("En la pos nro %d, está %d \n",x,arreglo[x]);
    }
}

int main(void){
    int array[50];

    completar_array(array);

    int tamanio=sizeof(array)/sizeof(array[0]);
    
    imprimir_array(array,tamanio);

    return 0;
}