// Ejercicio 13. Escriba un programa que lea un entero n entre 5 y 100 y luego solicite al usuario
// el ingreso de n enteros, los guarde a todos en un arreglo, y finalmente determine si la suma de
// los elementos del arreglo es mayor a 30. Si el usuario ingresa un número n menor a 5 o mayor
// a 100 entonces se deberá imprimir un mensaje de Error y el ingreso del arreglo y el análisis de
// su contenido no se realizará.

#include <stdio.h>

void completar_arreglo(int *array,int n){
    for (int x=0;x<n;x++){
        printf("Ingresa el entero nro %d: ",x+1);
        scanf("%d",&array[x]);
    }
}

int sumar_arreglo(int *array,int size){
    int suma=0;
    for(int x=0;x<size;x++){
        suma+=array[x];
    }
    return suma;
}

int main(void){
    int entero;

    printf("Ingrese un entero/ [5,100]: ");
    scanf("%d",&entero);
    if(entero<5 || entero>100){
        printf("ERROR. FUERA DEL RANGO");
        return 1;}
    
    int array[entero];

    completar_arreglo(array,entero);

    int tam=sizeof(array)/sizeof(array[0]);
    int suma=sumar_arreglo(array,tam);

    if(suma>30){
        printf("La suma de los elementos del arreglo es mayor a 30! \n");
    }

    printf("La suma fue %d",suma);
    
    return 0;
}