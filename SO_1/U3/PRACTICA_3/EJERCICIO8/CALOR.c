// Ej. 8 (Barreras). Una barrera para n threads tiene una ´unica operaci´on barrier_wait() que causa
// que los threads se pausen hasta que todos lleguen a la barrera. Son usadas, generalmente, para asegurar
// que las iteraciones de varios bucles en paralelo proceden a un mismo paso. Implemente una librer´ıa de
// barreras, exponiendo las funciones:
// void barrier_init(struct barrier *b, int n);
// void barrier_wait(struct barrier *b);
// Uselas para corregir el siguiente fragmento. La funci´on ´ calor() simula la transferencia de calor en un
// material, haciendo que cada elemento del array se “acerque” a sus vecinos, dejando el resultado de la
// transformaci´on en un nuevo array.
#define N 10

#include <pthread.h>
#include <stdio.h>

struct barrier {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int total;     // cantidad de hilos que deben llegar
    int count;     // cantidad de hilos que llegaron
    int phase;     // fase de sincronización (para evitar conflictos en múltiples usos)
};

void barrier_init(struct barrier *b, int n) {
    pthread_mutex_init(&b->lock, NULL);
    pthread_cond_init(&b->cond, NULL);
    b->total = n;
    b->count = 0;
    b->phase = 0;
}

void barrier_wait(struct barrier *b) {
    pthread_mutex_lock(&b->lock);
    int current_phase = b->phase;

    b->count++;

    if (b->count == b->total) {
        b->count = 0;
        b->phase++;  // cambia de fase
        pthread_cond_broadcast(&b->cond);
    } else {
        while (current_phase == b->phase)
            pthread_cond_wait(&b->cond, &b->lock);
    }

    pthread_mutex_unlock(&b->lock);
}


struct barrier barrera;

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
        pthread_barrier_wait(&barrera);
        calor(arr2, lo, hi, arr1);
        pthread_barrier_wait(&barrera);
    }
}


int main(){
    barrier_init(&barrier, N); // bloquea hasta que hay N

    pthread_t threads[N];

    for(int i=0;i<5;i++){
        pthread_create(&threads[i], NULL, thr,i+(void*)0);
    }
    for(int i=0;i<5;i++){
        pthread_join(threads[i], NULL);
    }
    pthread_barrier_destroy(&barrier);

     printf("Final result:\n");
    for (int i = 0; i < N; i++)
        printf("%.2f ", arr1[i]);
    printf("\n");

    return 0;
}