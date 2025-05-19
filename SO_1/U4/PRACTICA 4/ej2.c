#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <math.h>

// Ej. 2 (Suma Paralela). Escriba utilizando OpenMP un algoritmo que calcule la suma de un arreglo
// de N = 5 × 108 doubles. Compare la performance con la implementaci´on secuencial usando distintos
// n´umeros de hilos. Compare tambi´en con una versi´on paralela que usa un mutex para proteger la variable
// que lleva la suma.

#define N 100000
int main(){
    
    double arr[N], sum=0.0;
    #pragma omp parallel
    {
        #pragma omp for
        for(int x=0;x<N;x++){
            arr[x]=x;
            //printf(" %i\n",x);
        }
    }
    
    #pragma omp parallel for reduction(+: sum)
        for (int x=0;x<N;x++)
        {
        sum = sum + arr[x];
        }

    printf("sum: %f\n", sum);  //4999950000  (suma de 0 a N-1)

    return 0;

}

