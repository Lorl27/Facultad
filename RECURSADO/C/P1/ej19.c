// Ejercicio 19. La sucesión de Fibonacci se define de la siguiente manera:
// f(n) =
// 
// 
// 
// 0 si n = 0
// 1 si n = 1
// f(n − 1) + f(n − 2) si n > 2
// Escribir una función recursiva f que tome un entero n y devuelva el correspondiente valor
// según la sucesión de Fibonacci.

#include <stdio.h>
#include <assert.h>

double fibonacci(int n){
    if(n==0 || n==1){return n;}

    return (fibonacci(n-1)+fibonacci(n-2));

}

void test_fibonacci(void){
    assert(fibonacci(4)==3);
    assert(fibonacci(6)==8);
    assert(fibonacci(3)==2);
    assert(fibonacci(2)==1);
    assert(fibonacci(1)==1);
    assert(fibonacci(0)==0);
}

int main(void){

    test_fibonacci(); //TEST

    int numero;
    double resultado;

    printf("Ingresa el numero al cual quieras conocer su FIBONACCI: \n");
    scanf("%d",&numero);

    resultado=fibonacci(numero);

    printf("El numero fibonacci de %d es: %02.lf",numero,resultado);

    return 0;
}