// Ej.8(Barreras).Una barrera para n threads tiene una ´unica operaci´on barrier_wait() que causa que los threads se pausen hasta que todos lleguen a la barrera.
//Son usadas, generalmente, para asegurar que las iteraciones de varios bucles en paralelo proceden a un mismo paso.
//Implemente una librer´ıa de barreras, exponiendo las funciones : 
// void barrier_init(struct barrier *b, int n);
// void barrier_wait(struct barrier *b);

// Uselas para corregir el siguiente fragmento.La funci´on ´ calor() simula la transferencia de calor en un material,
// haciendo que cada elemento del array se “acerque” a sus vecinos, dejando el resultado de la transformaci´on en un nuevo array.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "barrier.h"



#define N 1000 
#define ITERS 100000
#define W 4  //nro de hilos (workers)

barrier barrera;

float arr1[N], arr2[N];


void calor(float *arr, int lo, int hi, float *arr2)
{
    int i;
    for (i = lo; i < hi; i++)
    {
        int m = arr[i];
        int l = i > 0 ? arr[i - 1] : m;
        int r = i < N - 1 ? arr[i + 1] : m;
        arr2[i] = m + (l - m) / 1000.0 + (r - m) / 1000.0;
    }
}

static inline int min(int a, int b) {
    return a < b ? a : b;
}

/* Dado un array de [n], devuelve el punto de corte [i] de los [m] totales. */
static inline int cut(int n, int i, int m)
{
    return i * (n / m) + min(i, n % m);
}


void *thr(void *arg)
{
    int id = arg - (void *)0; /* 0 <= id < W */
    int lo = cut(N, id, W), hi = cut(N, id + 1, W);
    int i;
    for (i = 0; i < ITERS; i++)
    {
        calor(arr1, lo, hi, arr2);
        barrier_wait(&barrera);  //esperamos que todas finalicen del arr1
        calor(arr2, lo, hi, arr1);
        barrier_wait(&barrera);  //todas deben finalizar del arr2.
    }

    return NULL;
}

int main(){

    pthread_t hilos[W];
    float f;
    int x;

    for(x=0;x<N;x++){
        arr1[x]=rand()/10000.0;
    }

    barrier_init(&barrera, W);

    for (int i = 0; i < W; i++) {
        pthread_create(&hilos[i], NULL, thr, i+(void *)0);
    }

    for (int i = 0; i < W; i++) {
        pthread_join(hilos[i], NULL);
    }

    f=0;
    for(x=0;x<N;x++){
        f+=arr1[x];
    }

    f/=N;

    printf("Temp promedio: %f \n", f); //deberia ser siempre ==


    return 0;
}