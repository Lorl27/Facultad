// Ej. 10 (Canales S´ıncronos). Un canal es una primitiva que permite el env´ıo de un valor entre threads.
// Que sea s´ıncrono implica que no s´olo el lector espera al escritor (obviamente) sino que el escritor no
// avanza hasta que haya aparecido un lector. Implemente canales s´ıncronos con la siguiente interfaz:

// Use su implementaci´on para implementar una soluci´on al problema de los (m´ultiples) productores y
// consumidores. ¿Qu´e ventajas y desventajas tiene?

#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1024

typedef struct channel{
    int valor;
    sem_t estado_escritor;
    sem_t estado_lector;
    sem_t mutex;
    int no_esta_lector; //0: esta y 1:no
    int esta_escritor;
    char buff[N];
    pthread_cond_t buffer_no_lleno, buffer_no_vacio;
    int ind_esc, ind_lec, cant_elem;
} Channel;


void channel_init(Channel *channel){
    channel->valor=0;
    sem_init(&channel->estado_escritor,0,0);
    sem_init(&channel->estado_lector,0,0);
    sem_init(&channel->mutex,0,1);
    channel->no_esta_lector=0;
    channel->esta_escritor=0;
    channel->ind_esc=0;
    channel->ind_lec=0;
    channel->cant_elem=0;
}

void chan_write(Channel *channel, int value){
    sem_wait(&channel->mutex);
    channel->esta_escritor=1;

    while(channel->no_esta_lector){
        sem_post(&channel->mutex);
        sem_wait(&channel->estado_lector);
        sem_wait(&channel->mutex);
    }

    //ya hay uno:
    while(channel->cant_elem == N){
        pthread_cond_wait(&channel->buffer_no_lleno, &channel->mutex);
    }

    channel->buff[channel->ind_esc] = value;
    channel->ind_esc = (channel->ind_esc + 1) % N;
    channel->cant_elem++;

    channel->esta_escritor=0;

    pthread_cond_signal(&channel->buffer_no_vacio);
    sem_post(&channel->mutex);

    return;

}

int chan_read(Channel *channel){
    sem_wait(&channel->mutex);

    channel->no_esta_lector=0; //esta
    
    while(channel->esta_escritor){
        sem_post(&channel->mutex);
        sem_wait(&channel->estado_escritor);
        sem_wait(&channel->mutex);
    }

    //espere al escritor- ahora leo yo 

    while(channel->cant_elem == 0){
        pthread_cond_wait(&channel->buffer_no_vacio, &channel->mutex);
    }
    
    int *p=malloc(sizeof(int));
    p=channel->buff[channel->ind_lec];
    channel->ind_lec = (channel->ind_lec + 1) % N;
    channel->cant_elem--;

    channel->esta_escritor=1;

    pthread_cond_signal(&channel->buffer_no_lleno);
    sem_post(&channel->mutex);

    return p;

}