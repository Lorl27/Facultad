#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5
#define N 5
#define SZ 8

/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */
int *buffer[SZ];

sem_t buffer_lleno;
sem_t buffer_vacio;
sem_t mutex;

int item_in,item_out;

void enviar(int *p)
{
    sem_wait(&buffer_vacio);

	sem_wait(&mutex);
	buffer[item_in]=p;
	item_in=(item_in+1)%SZ;
    sem_post(&mutex);

	sem_post(&buffer_lleno);
	
}

int * recibir()
{
	sem_wait(&buffer_lleno);

    sem_wait(&mutex);
	int *p=buffer[item_out];
	item_out=(item_out+1)%SZ;
    sem_post(&mutex);

	sem_post(&buffer_vacio);
	return p;
}

void * prod_f(void *arg)
{
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

		int *p = malloc(sizeof *p);
		*p = random() % 100;
		printf("Productor %d: produje %p->%d\n", id, p, *p);
		enviar(p);
	}
	return NULL;
}

void * cons_f(void *arg)
{
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

		int *p = recibir();
		printf("Consumidor %d: obtuve %p->%d\n", id, p, *p);
		free(p);
	}
	return NULL;
}

int main()
{
	pthread_t productores[M], consumidores[N];
	int i;

	sem_init(&mutex,0,1);
    sem_init(&buffer_lleno,0,0);
    sem_init(&buffer_vacio,0,SZ);

	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

	pthread_join(productores[0], NULL); /* Espera para siempre */
	return 0;
}