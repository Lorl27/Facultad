// Ejercicio 17. Analice el siguiente código e introduzca comentarios en cada línea indicando
// el objeto de la misma. Observar la 4ta línea a modo de ejemplo. El algoritmo expuesto data del
// siglo III a.C. y se lo denomina Criba de Eratóstenes. ¿Puede entender qué hace el programa?

#include <stdio.h>

#define N 1000

int main() {
    int i, j, a[N+1]; // linea 4: declaracion de dos enteros y un arreglo de 1001 componentes
    for (a[1]=0, i=2; i <= N; i++) {
        a[i] = 1;           // el 2do elemento del array es =0, y a partir del 2->100 es =1
    } //ES DECIR: marca todos esos nros como primos!

    for (i=2; i <= N/2; i++) { //agarra solo la mitad (1000/2:500)
        for (j=2; j <= N/i; j++) {  //agarra la mitad de la mitad
            a[i*j] = 0;             // cada multiplo de ambos=0 -> NO PRIMO
        }
    }
    for (i=1; i <= N; i++) {
        if(a[i]==1) {   //agarra los q indicamos previamente (LOS PRIMOS)
            printf(" %d", i);
        }
    }
    printf("\n");

    return 0; //Este código imprime los números primos hasta 1000!
}
