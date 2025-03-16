// Ejercicio 13. Escriba un programa que pida un número y, muestre el factorial de ese número.
// Sugerencia: definir la variable que represente el factorial como double.

#include <assert.h>
#include <stdio.h>

double factorial(int numero){
    double factorial=1;
    for(int x=1;x<=numero;x++){
        factorial*= x;
    }
    return factorial;
}

void test_factorial(void){
    assert(factorial(5)==120);
    assert(factorial(1)==1);
    assert(factorial(0)==1);
    assert(factorial(10)==3628800);
    assert(factorial(4)==24);
    assert(factorial(2)==2);
}


int main(void){
    test_factorial(); // TESTS

    int numero;
    double resultado;
    printf("ingrese el numero al que desea descubrir su factorial:\n");
    scanf("%d",&numero);

    resultado=factorial(numero);
    printf("El factorial de %d es %02.lf",numero,resultado);
    return 0;
}