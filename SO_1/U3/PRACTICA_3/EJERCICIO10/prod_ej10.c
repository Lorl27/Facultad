#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5
#define NO 5
/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */

#define N 1024

typedef struct channel{
    int valor;
    sem_t estado_escritor;
    sem_t estado_lector;
    pthread_mutex_t mutex;
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
    pthread_mutex_init(&channel->mutex,NULL);
    channel->no_esta_lector=0;
    channel->esta_escritor=0;
    channel->ind_esc=0;
    channel->ind_lec=0;
    channel->cant_elem=0;
}

void chan_write(Channel *channel, int *value){
    pthread_mutex_lock(&channel->mutex);
    channel->esta_escritor=1;

    while(channel->no_esta_lector){
        pthread_mutex_unlock(&channel->mutex);
        sem_wait(&channel->estado_lector);
        pthread_mutex_lock(&channel->mutex);
    }

    //ya hay uno:
    while(channel->cant_elem == N){
        pthread_cond_wait(&channel->buffer_no_lleno, &channel->mutex);
    }

    channel->buff[channel->ind_esc] = *value;
    channel->ind_esc = (channel->ind_esc + 1) % N;
    channel->cant_elem++;

    channel->esta_escritor=0;

    pthread_cond_signal(&channel->buffer_no_vacio);
    pthread_mutex_unlock(&channel->mutex);

    return;

}

int* chan_read(Channel *channel){
    pthread_mutex_lock(&channel->mutex);

    channel->no_esta_lector=0; //esta
    
    while(channel->esta_escritor){
        pthread_mutex_unlock(&channel->mutex);
        sem_wait(&channel->estado_escritor);
        pthread_mutex_lock(&channel->mutex);
    }

    //espere al escritor- ahora leo yo 

    while(channel->cant_elem == 0){
        pthread_cond_wait(&channel->buffer_no_vacio, &channel->mutex);
    }
    
    int *p=malloc(sizeof(int));
    *p=channel->buff[channel->ind_lec];
    channel->ind_lec = (channel->ind_lec + 1) % N;
    channel->cant_elem--;

    channel->esta_escritor=1;

    pthread_cond_signal(&channel->buffer_no_lleno);
    pthread_mutex_unlock(&channel->mutex);

    return p;

}

Channel c;

void * prod_f(void *arg)
{
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

		int *p = malloc(sizeof *p);
		*p = random() % 100;
		printf("Productor %d: produje %p->%d\n", id, p, *p);
		chan_write(&c,p);
	}
	return NULL;
}

void * cons_f(void *arg)
{
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

		int *p = chan_read(&c);
		printf("Consumidor %d: obtuve %p->%d\n", id, p, *p);
		free(p);
	}
	return NULL;
}

int main()
{
	pthread_t productores[M], consumidores[NO];
	int i;
    channel_init(&c);

	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < NO; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

	pthread_join(productores[0], NULL); /* Espera para siempre */
	return 0;
}
