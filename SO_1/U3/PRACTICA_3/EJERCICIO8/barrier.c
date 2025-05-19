#include <pthread.h>
#include "barrier.h"

void barrier_init(barrier *b, int n){

    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->proceder, NULL);
    pthread_cond_init(&b->restaurado, NULL);

    b->n = n;
    b->desbloqueado = 0;
    b->bloqueado = 0;
}

void barrier_wait(barrier *b) {
    pthread_mutex_lock(&b->mutex);
    while (b->bloqueado == b->n)
        pthread_cond_wait(&b->restaurado, &b->mutex);

    b->bloqueado++;
    while (b->bloqueado < b->n) {
        pthread_cond_wait(&b->proceder, &b->mutex);
    }
    pthread_cond_broadcast(&b->proceder);
    b->desbloqueado++;

    if (b->desbloqueado == b->n) {
        b->bloqueado = b->desbloqueado = 0;
        pthread_cond_broadcast(&b->restaurado);
    }
    pthread_mutex_unlock(&b->mutex);
}