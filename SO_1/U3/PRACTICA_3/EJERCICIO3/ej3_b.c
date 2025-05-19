// Ej. 3 (Productor-Consumidor, Dijkstra). En un sistema, hay M procesos llamados “productores”
// que generan valores (digamos, de tipo int) y N procesos “consumidores” que los leen y realizan alguna
// computaci´on con ellos. Se debe garantizar que:
// cada valor producido sea consumido, es decir, que no se pierda
// cada valor producido no sea tomado por m´as de un consumidor
// Los procesos se comunican mediante un buffer compartido, insertando y tomando elementos del mismo.
// En este ejemplo (ver prod-cons.c), los productores alocan un entero con malloc() y los consumidores
// los liberan con free(). Perder elementos producidos implica una fuga de memoria, y consumirlos dos
// veces implica un doble-free.
// a) Implemente una soluci´on usando sem´aforos para llevar las cantidades de elementos en el buffer, y la
// cantidad de elementos libres.
// b) Implemente una soluci´on usando variables de condici´on.

//----------------------------------
#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/* Producer/consumer program illustrating conditional variables */
pthread_mutex_t mutex_v=PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_hay_lugar= PTHREAD_COND_INITIALIZER; //var condicion
pthread_cond_t cond_hay_elemento= PTHREAD_COND_INITIALIZER; //var condicion


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
		pthread_mutex_lock(&mutex_v);

		/* SEMANTICA MESA -*/
		while(num==BUF_SIZE){//buffer lleno
			printf("[producer] waiting...\n");
			pthread_cond_wait(&cond_hay_lugar,&mutex_v);
		}
		/* - FIN SEMANTICA MESA*/

		
		/* Insert into buffer */
		if (num > BUF_SIZE) exit(1);	/* overflow */

		/* if executing here, buffer not full so add element */
		buffer[add] = i;
		add = (add+1) % BUF_SIZE;
		num++;
		printf ("producer: inserted %d\n", i);  fflush (stdout);
		pthread_cond_signal(&cond_hay_elemento); //si no hay nadie en el wait, en el peor de los casos l señal se pierde (idc about that!)
		pthread_mutex_unlock(&mutex_v);
	}
	printf ("producer quiting\n");  fflush (stdout);
}

/* Consume value(s); Note the consumer never terminates */
void *consumer(void *param)
{
	int i;
	while (1) {
		pthread_mutex_lock(&mutex_v);

		while(num==0){//buffer lleno
			printf("[consumer] waiting...\n");
			pthread_cond_wait(&cond_hay_elemento,&mutex_v);
		}

		if (num < 0) exit(1);   /* underflow */

		/* if executing here, buffer not empty so remove element */
		i = buffer[rem];
		rem = (rem+1) % BUF_SIZE;
		num--;
   		printf ("Consume value %d\n", i);  fflush(stdout);
		pthread_cond_signal(&cond_hay_lugar);
		pthread_mutex_unlock(&mutex_v);
	}
}

int main (int argc, char *argv[])
{
	pthread_t tid1, tid2;		/* thread identifiers */
	int i;

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