// Ejercicio 7:
//? Un año es bisiesto si es divisible por 4 y no es por 100, o si es divisible por 400.
// Escriba un programa que lea un año y devuelva si es bisiesto o no.

#include <stdio.h>

int bisiesto(int year){
    return (year%4==0 && year%100!=0) || (year%400==0);
}

int main(){
    int input_u;

    printf("Ingrese el año del que desea saber si es Bisiesto o no: \n");
    scanf("%d",&input_u);

    if(!bisiesto(input_u)){
        printf("El año %d NO es bisiesto",input_u);
    }
    else{
        printf("El año %d es bisiesto",input_u);
    }

    return 0;
}