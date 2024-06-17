// Ejercicio 10. Escriba un programa que llene un arreglo con los números pares que se en-
// cuentren entre 100 y 200 y los muestre en pantalla en orden descendente.

#include <stdio.h>

int main(){
    int arr[200];
    for (int x=200;x>=100;x--){
        if(x%2==0){
        arr[x]=x;
        printf("%d \n",arr[x]);}
        
    }
    }