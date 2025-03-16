// 3. Bucle While
// Ejercicio 9. Escriba un programa que muestre los números enteros del 1 al 100.

#include <stdio.h>
#include <assert.h>

int main(){
    int numero=1;
    while(numero<101){
        printf("El número es: %d",numero);
        numero+=1;
    }
    return 0;
}