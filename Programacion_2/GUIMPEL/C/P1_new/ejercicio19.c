// Ejercicio 19: La sucesión de Fibonacci se define de la siguiente manera:
// f (n) = {
//         0 si n = 0,
//         1 si n = 1,
//         f (n −1) + f (n −2) si n > 2
//         }
// Escribir una función recursiva f que tome un entero n y devuelva el correspondiente valor, según la sucesión de Fibonacci.


#include <stdio.h>

int fibonnacci(int n){
    if (n==0 || n==1){ return n;}

    return fibonnacci(n-1)+fibonnacci(n-2);
}

int main(){
    int n,rta;

    printf("Ingrese un nro, para saber su fibonacci. \n");
    scanf("%d",&n);

    rta=fibonnacci(n);

    printf("El fibonacci de %d , es: %d ",n,rta);

    return 0;

}
