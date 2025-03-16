// Ejercicio 13: Escriba un programa que pida un número y, muestre el factorial de ese número.

//* Sugerencia: definir la variable que represente el factorial como double.

#include <stdio.h>

double factorial(double nro){
    if (nro==1 || nro==0){
        return 1;
    }

    return(nro*factorial(nro-1));
}

int main(){
    double nro,resultado;
    printf("Ingrese el nro: \n");
    scanf("%lf",&nro);

    resultado=factorial(nro);

    printf("El factorial de %lf es %lf",nro,resultado);

    return 0;
}