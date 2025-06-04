// Ej.6(Quicksort).Recordemos el algoritmo de ordenamiento Quicksort :
/* Particion de Lomuto, tomando el primer elemento como pivote */

#include <unistd.h>  //sleep
#include <stdlib.h>  //exit y malloc
#include <stdio.h>  //f. básicas como print
#include <pthread.h> //API: MUTEX POSIX. incluir en gcc -pthread
#include <omp.h>

#define NTHREADS 4

int swap(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int particionar(int a[], int N){
    int i, j = 0;
    int p = a[0];
    swap(&a[0], &a[N - 1]);
    for (i = 0; i < N - 1; i++) {
        if (a[i] <= p)
            swap(&a[i], &a[j++]);
    }
    swap(&a[j], &a[N - 1]);
    return j;
}

void qsort1(int a[], int N) {
    if (N < 2)
        return;
    int p = particionar(a, N);
    qsort1(a, p);
    qsort1(a + p + 1, N - p - 1);
}

int main(){
    int a[]={1,3,4,8,9};

    #pragma omp parallel
    {

        #pragma omp task
        {
            qsort1(a,5);
        }

    }


    return 0;

}

// Dado que las llamadas recursivas para ordenar las “mitades” del arreglo son independientes, son un claro candidato para paralelizar.


// b)Escriba una versi´on que paralelice las llamadas usando sections de OpenMP. ¿Mejora la perfor - mance ? ¿Cu´anto ? 
//Puede usar el servidor labdcc para probar en un quad - core.

// c)Escriba una versi´on usando tasks de OpenMP y mida el cambio en rendimiento.