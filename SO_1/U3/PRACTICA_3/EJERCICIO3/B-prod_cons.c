#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define M 5
#define N 5
#define SZ 8

/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */
int *buffer[SZ];

pthread_cond_t cond_buffer_lleno=PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_buffer_vacio=PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex;

int item_in,item_out,contador=0;

void enviar(int *p)
{
	pthread_mutex_lock(&mutex);
	while(contador == SZ){
		pthread_cond_wait(&cond_buffer_vacio,&mutex);
	}
	buffer[item_in]=p;
	item_in=(item_in+1)%SZ;
	contador++;
	pthread_cond_signal(&cond_buffer_lleno);
	pthread_mutex_unlock(&mutex);
	
}

int * recibir()
{
	pthread_mutex_lock(&mutex);
	while(contador == 0){
		pthread_cond_wait(&cond_buffer_lleno,&mutex);
	}
	int *p=buffer[item_out];
	item_out=(item_out+1)%SZ;
	contador--;
	pthread_cond_signal(&cond_buffer_vacio);
	pthread_mutex_unlock(&mutex);
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

	pthread_mutex_init(&mutex,NULL);

	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

	pthread_join(productores[0], NULL); /* Espera para siempre */
	return 0;
}