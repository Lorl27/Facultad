#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#include "rwlock.h"

struct rwlock {
    sem_t queue;         // Cola de espera FIFO (justicia)
    sem_t mutex;         // Protege el acceso a las variables internas
    sem_t lectorOK;      // Para bloquear lectores cuando un escritor está escribiendo

    int lectores_activos;
    int escritores_activos;
    int lectores_esperando;
};

struct rwlock *rwlock_init() {
    struct rwlock *rwl = malloc(sizeof(struct rwlock));
    sem_init(&rwl->queue, 0, 1);
    sem_init(&rwl->mutex, 0, 1);
    sem_init(&rwl->lectorOK, 0, 1);

    rwl->lectores_activos = 0;
    rwl->escritores_activos = 0;
    rwl->lectores_esperando = 0;
    return rwl;
}

void rwlock_destroy(struct rwlock *rwl) {
    sem_destroy(&rwl->queue);
    sem_destroy(&rwl->mutex);
    sem_destroy(&rwl->lectorOK);
    free(rwl);
}

void lock_r(struct rwlock *rwl) {
    sem_wait(&rwl->queue);         // Turno justo para entrar
    sem_wait(&rwl->mutex);
    rwl->lectores_esperando++;
    if (rwl->lectores_activos == 0)
        sem_wait(&rwl->lectorOK);  // Bloquear si un escritor está activo
    rwl->lectores_activos++;
    rwl->lectores_esperando--;
    sem_post(&rwl->mutex);
    sem_post(&rwl->queue);         // Dejo pasar al siguiente en la cola
}

void unlock_r(struct rwlock *rwl) {
    sem_wait(&rwl->mutex);
    rwl->lectores_activos--;
    if (rwl->lectores_activos == 0)
        sem_post(&rwl->lectorOK);  // El último lector libera a escritores
    sem_post(&rwl->mutex);
}

void lock_w(struct rwlock *rwl) {
    sem_wait(&rwl->queue);        // Turno justo para entrar
    sem_wait(&rwl->lectorOK);     // Espera a que no haya lectores leyendo
    sem_wait(&rwl->mutex);
    rwl->escritores_activos = 1;
    sem_post(&rwl->mutex);
}

void unlock_w(struct rwlock *rwl) {
    sem_wait(&rwl->mutex);
    rwl->escritores_activos = 0;
    sem_post(&rwl->mutex);
    sem_post(&rwl->lectorOK);   // Permite entrada a lectores/escritores
    sem_post(&rwl->queue);      // Deja pasar al siguiente en la cola
}
