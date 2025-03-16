// Ejercicio 13. Escriba un programa que lea un entero n entre 5 y 100 y luego solicite al usuario
// el ingreso de n enteros, los cuales debe guardar en un arreglo. Finalmente, debe determinar si
// la suma de los elementos del arreglo es mayor a 30. Si el usuario ingresa un número n menor
// a 5 o mayor a 100 entonces se deberá imprimir un mensaje de Error y el ingreso del arreglo y
// el análisis de su contenido no se realizará.

#include <stdio.h>

int main(){
    int entero;
    int n;
    int suma=0;

    printf("Ingrese un entero entre [5..100]\n");
    scanf("%d",&entero);
    if(entero<5 || entero>100){
        printf("Error.");
        return 1;
    }

    int array[entero];

    printf("Ingrese %d enteros\n:",entero);
    for(int x=0;x<entero;x++){
        scanf("%d",&n);
        array[x]=n;
        suma+=n;
    }

    if(suma>30){
        printf("Su suma es mayor a 30 (%d )\n",suma);}
    else{printf("su suma es menor o igual a 30,( %d)\n",suma);}
    
    return 0;
}
