//Ejercicio 11. Escriba un programa que llene un arreglo con los primeros 50 múltiplos de 3 y
//los muestre en pantalla en orden descendente.

#include <stdio.h>

#include <stdio.h>

int main(){
    int arr[50]; 
    int index = 0; // Variable para seguir el índice correcto del arreglo

    for (int x=1; x<= 50; x++) {
        arr[index] = x*3; // Almacena el múltiplo de 3 en el arreglo
        index++;
    }

    // Imprimir en orden descendente
    for (int i=49; i >=0; i--){
        printf("%d\n", arr[i]);
    }

    return 0;
}
