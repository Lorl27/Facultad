// Ejercicio 7. Un anio es bisiesto si es divisible por 4 y no es por 100, o si es divisible por 400.
// Escriba un programa que lea un anio y devuelva si es bisiesto o no.

#include <stdio.h>
#include <assert.h>

int bisiesto(int anio){
    return (anio%4==0 && anio%100!=0) || (anio%400==0);
}


void test_bisiesto(void){
    assert(bisiesto(2004)==1); //bisiesto
    assert(bisiesto(2005)==0); // NO bisiesto
    assert(bisiesto(1990)==0); //bisiesto
}

int main(){
    int anio=0,resultado;
    printf("Ingresa el anio de tu interés: ");
    scanf("%d",&anio);
    resultado=bisiesto(anio);
    if (resultado){
        printf("El anio %d es bisiesto",anio);
    }else{printf("El anio %d NO es bisiesto",anio);}

    test_bisiesto(); //tests
    return 0;
}
