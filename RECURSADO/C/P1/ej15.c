// 4. Funciones
// Ejercicio 15. Escribir una función maximo que tome como parámetro dos enteros y devuelva
// el máximo entre ellos. Utilizar esa función para calcular el máximo entre 4 enteros que se le
// soliciten al usuario.

#include <stdio.h>
#include <assert.h>
#include "ej15.h"


int maximum(int a, int b){
    return (a>b)?a:b;
}

void test_maximum(void){
    assert(maximum(5,4)==5);
    assert(maximum(5,40)==40);
}

int maximum_4(int a,int b,int c, int d){
    return maximum(maximum(a,b),maximum(c,d));
}

void test_maximum_4(void){
    assert(maximum_4(5,4,3,2)==5);
    assert(maximum_4(5,40,3,2)==40);
    assert(maximum_4(5,4,30,2)==30);
    assert(maximum_4(5,4,3,20)==20);
}

int main(void){

    // TESTEOS:
    test_maximum();
    test_maximum_4();

    int a,b,c,d,resultado=0;

    printf("Ingrese los 4 numeros a evaluar: \n");
    scanf("%d%d%d%d",&a,&b,&c,&d);

    resultado=maximum_4(a,b,c,d);

    printf("El mayor numero entre los 4 es %d",resultado);

    return 0;
}

//note: para usar en 'ej16.c' comentar MAIN.