#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define B 5

int buf[B];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *prod(void *_arg) {
    int id = *((int *)_arg);
    int val = 0;

    while (1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buf[in] = val++;
        printf("Productor %d escribió %d en pos %d\n", id, val-1, in);
        in = (in + 1) % B;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *cons(void *_arg) {
    int id = *((int *)_arg);
    int val;

    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        val = buf[out];
        printf("Consumidor %d leyó %d de pos %d\n", id, val, out);
        out = (out + 1) % B;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    int i, N = 2;
    pthread_t productores[N], consumidores[N];
    int ids[N];

    sem_init(&empty, 0, B);
    sem_init(&full, 0, 0);

    for (i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&productores[i], NULL, prod, &ids[i]);
        pthread_create(&consumidores[i], NULL, cons, &ids[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(productores[i], NULL);
        pthread_join(consumidores[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
