///similar a los semaforos del tren . son otra forma de sinceonizacion . son objetos concurrentes q representan la idea de  un contador

// no baja de 0 . si el semaforo esta en cero y hago down, me quedo block.

#include <semaphore.h>

//shared compartido entre procesos creados con fork, si vale 1 es para prcesos . 0 para threads

#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Producer/consumer program illustrating conditional variables */
pthread_mutex_t mutex_v=PTHREAD_MUTEX_INITIALIZER;

sem_t lugares_libres_sem;
sem_t lugares_ocupados_sem;

/* Size of shared buffer */
#define BUF_SIZE 3

int buffer[BUF_SIZE];					/* shared buffer */
int add=0;										/* place to add next element */
int rem=0;										/* place to remove next element */
int num=0;										/* number elements in buffer */

/* Produce value(s) */
void *producer(void *param)
{
	int i;
	for (i=1; i<=20; i++) {

        sem_wait(&lugares_libres_sem);
		pthread_mutex_lock(&mutex_v);

	
		/* Insert into buffer */
		if (num > BUF_SIZE) exit(1);	/* overflow */

		/* if executing here, buffer not full so add element */
		buffer[add] = i;
		add = (add+1) % BUF_SIZE;
		num++;
		printf ("producer: inserted %d\n", i);  fflush (stdout);
		
		pthread_mutex_unlock(&mutex_v);
        sem_post(&lugares_ocupados_sem); 
	}
	printf ("producer quiting\n");  fflush (stdout);
}

/* Consume value(s); Note the consumer never terminates */
void *consumer(void *param)
{
	int i;
	while (1) {
        sem_wait(&lugares_ocupados_sem);  //down
		pthread_mutex_lock(&mutex_v);


		if (num < 0) exit(1);   /* underflow */

		/* if executing here, buffer not empty so remove element */
		i = buffer[rem];
		rem = (rem+1) % BUF_SIZE;
		num--;
   		printf ("Consume value %d\n", i);  fflush(stdout);
		
		pthread_mutex_unlock(&mutex_v);
        sem_post(&lugares_libres_sem);  //up
	}
}

int main (int argc, char *argv[])
{
	pthread_t tid1, tid2;		/* thread identifiers */
	int i;
    sem_init(&lugares_libres_sem,0,BUF_SIZE); //para threads:no compartido en dif proceos.
    sem_init(&lugares_ocupados_sem,0,BUF_SIZE); 
	/* create the threads; may be any number, in general */
	if (pthread_create(&tid1,NULL,producer,NULL) != 0) {
		fprintf (stderr, "Unable to create producer thread\n");
		exit (1);
	}
	if (pthread_create(&tid2,NULL,consumer,NULL) != 0) {
		fprintf (stderr, "Unable to create consumer thread\n");
		exit (1);
	}
	/* wait for created thread to exit */
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf ("Parent quiting\n");
}