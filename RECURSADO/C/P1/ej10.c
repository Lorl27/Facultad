// Ejercicio 10. Escriba un programa que muestre los números impares del 1 al 100.

#include <stdio.h>
#include <assert.h>

int main(){
    int numero=1;
    while(numero<101){
        if(numero%2!=0){printf("El numero es: %d",numero);}
        numero+=1;
    }
    return 0;
}