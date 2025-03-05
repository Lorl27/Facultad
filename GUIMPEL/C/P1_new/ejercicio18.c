// Ejercicio 18: La fecha del domingo de Pascua corresponde al primer domingo después de la primera luna llena que sigue al equinoccio de primavera. 
// Dado un año, los cálculos que permiten conocer esta fecha son:
// A = año %19
// B = año % 4
// C = año % 7
// D = (19 * A + 24) % 30
// E = (2 * B + 4 * C + 6 * D + 5) % 7
// N = (22 + D + E), Donde N indica el número del día del mes de marzo (o abril si N es superior a 31) correspondiente al domingo de Pascua.
// Escribir un programa que lea un año y muestre el día y el mes en el que se celebró o se celebrará el domingo de Pascua ese año.
//Utilizar una función a la que se le pase como parámetro el año y retorne el valor de N. 
// El programa principal realiza el resto del proceso

#include <stdio.h>

int calculo(int year){
    int n=0,a=0,b=0,c=0,d=0,e=0;

    a=year%19;
    b=year%4;
    c=year%7;
    d=(19*a+24)%30;
    e=(2*b+4*c+6*d+5)%7;

    n= 22+d+e;

    return n;

}

void mes_arreglo(int n){
    n>31? printf("Abril") : printf("Marzo");
}

int main(){
    int year,n;

    printf("Ingrese un año, para saber cuándo cayó/cae/caerá Pascua en el mismo. \n");
    scanf("%d",&year);

    n=calculo(year);

    printf("Pascua: año: %d , dia: %d , mes:  ", year,(n>31?n-31:n));
    mes_arreglo(n);

    return 0;

}


//NOTE - Por fin lo arreglé ;).