// Ejercicio 15. Escriba una función sumaArr que tome un arreglo de enteros junto con la longi-
// tud del mismo y devuelva la suma de sus elementos.

#include <stdio.h>

int sumaArr(int arr[],int longitud){
    int suma=0;
    for(int x=0;x<longitud;x++){
        suma+=arr[x];
    }
    return suma;

}

int main() {
    int arreglo[] = {5, 10, 15, 20, 25};
    int longitud = sizeof(arreglo) / sizeof(arreglo[0]); // Calcula la longitud del arreglo

    // Llamada a la función sumaArr
    int resultado = sumaArr(arreglo, longitud);

    // Imprimir el resultado
    printf("La suma de los elementos del arreglo es: %d\n", resultado);

    return 0;
}