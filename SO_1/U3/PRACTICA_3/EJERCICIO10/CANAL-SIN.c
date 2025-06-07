#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valor;                   // valor a transferir
    int hay_writer;              // bandera: hay escritor esperando
    int hay_reader;              // bandera: hay lector esperando
    pthread_mutex_t mutex;
    pthread_cond_t cond_writer; // cond para que el writer espere al reader
    pthread_cond_t cond_reader; // cond para que el reader espere al writer
} Channel;

void channel_init(Channel *c) {
    c->hay_writer = 0;
    c->hay_reader = 0;
    pthread_mutex_init(&c->mutex, NULL);
    pthread_cond_init(&c->cond_writer, NULL);
    pthread_cond_init(&c->cond_reader, NULL);
}

// writer: espera a que haya reader → pasa el valor → ambos continúan
void chan_write(Channel *c, int *value) {
    pthread_mutex_lock(&c->mutex);

    while (c->hay_writer) // solo un writer a la vez
        pthread_cond_wait(&c->cond_writer, &c->mutex);

    c->hay_writer = 1;
    c->valor = *value;

    // si no hay lector, esperar
    while (!c->hay_reader)
        pthread_cond_wait(&c->cond_reader, &c->mutex);

    // hay lector esperando: despertarlo
    pthread_cond_signal(&c->cond_reader);

    c->hay_writer = 0;
    pthread_cond_signal(&c->cond_writer); // permitir otro writer
    pthread_mutex_unlock(&c->mutex);
}

// reader: espera a que haya writer → toma el valor
int *chan_read(Channel *c) {
    pthread_mutex_lock(&c->mutex);

    while (c->hay_reader) // solo un reader a la vez
        pthread_cond_wait(&c->cond_reader, &c->mutex);

    c->hay_reader = 1;

    // si no hay escritor, esperar
    while (!c->hay_writer)
        pthread_cond_wait(&c->cond_reader, &c->mutex);

    // hay escritor → tomar valor
    int *p = malloc(sizeof(int));
    *p = c->valor;

    c->hay_reader = 0;
    pthread_cond_signal(&c->cond_reader); // permitir otro reader
    pthread_mutex_unlock(&c->mutex);
    return p;
}
