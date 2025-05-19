// Ej. 3 (B´usqueda del M´ınimo). Escriba utilizando OpenMP un algoritmo que dado un arreglo de
// N = 5 × 108 enteros busque el m´ınimo. Compare la performance con la implementaci´on secuencial con
// distinto n´umero de hilos.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <math.h>
#include <limits.h>

#define N 5

int main(){
    double arr[N]={4,6,9,19,-5};
    double minimo=INT_MAX;

    #pragma omp parallel for reduction(min:minimo)
    for(int x=0;x<N;x++){
        if(minimo>arr[x]){
            minimo=arr[x];
        }
    }

    printf("MINIMO: %f",minimo);
    return 0;
}
