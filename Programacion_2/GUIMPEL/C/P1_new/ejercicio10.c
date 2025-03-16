// Ejercicio 10: Escriba un programa que muestre los números impares del 1 al 100.


#include <stdio.h>


int main(){
    int contador=1;
    while(contador<=100){
        if(contador%2==0){
    printf("%d\t",contador);}
    contador++;
    }

    return 0;
}