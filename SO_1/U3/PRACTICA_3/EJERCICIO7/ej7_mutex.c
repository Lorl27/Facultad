#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define B 5  // tamaño del buffer

int buf[B];
int in = 0, out = 0, count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full  = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void *prod(void *_arg) {
    int id = *((int *)_arg);
    int val = 0;

    while (1) {
        pthread_mutex_lock(&mutex);

        while (count == B)
            pthread_cond_wait(&not_full, &mutex);

        buf[in] = val++;
        printf("Productor %d escribió %d en pos %d\n", id, val-1, in);
        in = (in + 1) % B;
        count++;

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *cons(void *_arg) {
    int id = *((int *)_arg);
    int val;

    while (1) {
        pthread_mutex_lock(&mutex);

        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        val = buf[out];
        printf("Consumidor %d leyó %d de pos %d\n", id, val, out);
        out = (out + 1) % B;
        count--;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    int i, N = 2;
    pthread_t productores[N], consumidores[N];
    int ids[N];

    for (i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&productores[i], NULL, prod, &ids[i]);
        pthread_create(&consumidores[i], NULL, cons, &ids[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(productores[i], NULL);
        pthread_join(consumidores[i], NULL);
    }

    return 0;
}
