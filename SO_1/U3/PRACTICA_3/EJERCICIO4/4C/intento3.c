#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

#include "rwlock.h"

struct rwlock {
    int lectores_leyendo;
    int escritores_escribiendo;

    int lectores_esperando;
    int escritores_esperando;

    sem_t mutex;
    sem_t cola; // todos esperan acá
};

struct rwlock *rwlock_init() {
    struct rwlock *rwl = malloc(sizeof(struct rwlock));
    rwl->lectores_leyendo = 0;
    rwl->escritores_escribiendo = 0;
    rwl->lectores_esperando = 0;
    rwl->escritores_esperando = 0;

    sem_init(&rwl->mutex, 0, 1);
    sem_init(&rwl->cola, 0, 0);

    return rwl;
}

void rwlock_destroy(struct rwlock *rwl) {
    sem_destroy(&rwl->mutex);
    sem_destroy(&rwl->cola);
    free(rwl);
}

void lock_r(struct rwlock *rwl) {
    sem_wait(&rwl->mutex);
    if (rwl->escritores_escribiendo > 0 || rwl->escritores_esperando > 0) {
        rwl->lectores_esperando++;
        sem_post(&rwl->mutex);
        sem_wait(&rwl->cola);
        sem_wait(&rwl->mutex);
        rwl->lectores_esperando--;
    }
    rwl->lectores_leyendo++;
    sem_post(&rwl->mutex);
}


void unlock_r(struct rwlock *rwl) {
    sem_wait(&rwl->mutex);
    rwl->lectores_leyendo--;

    if (rwl->lectores_leyendo == 0 && rwl->escritores_esperando > 0) {
        sem_post(&rwl->cola); // deja pasar al siguiente
    }
    sem_post(&rwl->mutex);
}


void lock_w(struct rwlock *rwl) {
    sem_wait(&rwl->mutex);
    if (rwl->lectores_leyendo > 0 || rwl->escritores_escribiendo > 0) {
        rwl->escritores_esperando++;
        sem_post(&rwl->mutex);
        sem_wait(&rwl->cola);
        sem_wait(&rwl->mutex);
        rwl->escritores_esperando--;
    }
    rwl->escritores_escribiendo++;
    sem_post(&rwl->mutex);
}


void unlock_w(struct rwlock *rwl) {
    sem_wait(&rwl->mutex);
    rwl->escritores_escribiendo--;

    if (rwl->escritores_esperando > 0) {
        sem_post(&rwl->cola); // escritor tiene prioridad si llegó antes
    } else if (rwl->lectores_esperando > 0) {
        // Despertar a todos los lectores en espera
        for (int i = 0; i < rwl->lectores_esperando; i++) {
            sem_post(&rwl->cola);
        }
    }
    sem_post(&rwl->mutex);
}


