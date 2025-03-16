// Ejercicio 17. Analice el siguiente código e introduzca comentarios en cada línea indicando el
// propósito de la misma. Observar la 4ta línea a modo de ejemplo. El algoritmo expuesto data del
// siglo III a.C. y se lo denomina Criba de Eratóstenes. ¿Puede entender qué hace el programa?

#include <stdio.h>
#define N 1000 //cambie esto pq estaba mal el formato!

int main()
{
    int i, j, a[N + 1]; // linea 4: declaracion de dos enteros y un arreglo de 1001 componentes

    for (a[1]=0, i =2; i<=N; i++) //descarta el primero
    {
        a[i] = 1; //vuelve todos sus elemeniso(menos el primero y 2do[==0] en 1.)
    }

    for (i=2; i<= N/2; i++)
    {
        for (j=2; j<= N/i; j++) //coreccion de error
        {
            a[i * j] = 0; //i<=500;j<=2... a[4]=0...a[1000]=0 (desde el 4 hasta el penultimo=0)
            //Para cada número i, establece como no primo (0) todos sus múltiplos.
        }
    }

    //Estas líneas de código marcan los múltiplos de cada número en el array a como no primos.
    //  Si un número i es primo, entonces todos sus múltiplos i * j también serán primos.
    //   Por lo tanto, si un número i * j es marcar como no primo, 
    //   entonces i y j también se marcarán como no primos

    //hasta ahora:a[1001]={a[0],1,1,1,0,.....,0}

    for (i=1; i<=N; i++)
    {
        if (a[i]==0) //corecion de error
        {
            printf(" %d ", i); //imprime cada indice(a partir del 1) del array SI su elemento es=0
            //imprime todos los números no primos (es decir, sus valores en el array a son 0)
        }
    }
    printf("\n");
    return 0;

    //Si un número es primo, su correspondiente valor en el array a será 0; de lo contrario, será 1
    //(imprime todos los n. NO primos)
}