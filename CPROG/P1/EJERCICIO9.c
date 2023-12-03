// 3. Arrays
// Ejercicio 9. Escriba un programa que llene un arreglo con los primeros 100 números enteros
// a partir del 0 y los muestre en pantalla en orden ascendente

#include <stdio.h>

int main(){
    int p[100];
    for(int x=0;x<=100;x++){
        p[x]=x;
        printf("%d \n",p[x]);
    }
}