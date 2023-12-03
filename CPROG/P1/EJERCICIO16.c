// Ejercicio 16. Escriba una función prodAlt que tome un arreglo de enteros junto con la longi-
// tud del mismo y devuelva el producto de los elementos cuyos índices son pares

#include <stdio.h>

int prodAlt(int arr[],int longitud){
    int producto=1;
    for(int x=0;x<longitud;x++){
        if((x%2)==0){
            producto*=arr[x];
        }
    }
    return producto;
}

int main(){
    int arr[]={1,2,3,4,5};
    int longitud= (sizeof(arr)/sizeof(arr[0]));

    int resultado= prodAlt(arr,longitud);
    printf("El producto de todos elemtos de indice par es %d\n",resultado);
}

