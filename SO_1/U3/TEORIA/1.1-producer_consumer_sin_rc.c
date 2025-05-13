//var cond. always asociadas con u nmutex.
/* consumir , con signla despiert al menos a un porcesador y  broadcst despierta a todos: ocmpetiran x le lock*/
// man pthread_cond_signal

//--------**EN VAR DE COND
//siempre tomo el lokck primero y dsp viene el while!!

//cond weit lo bloquea entonces no onsume procesador. -- l a var de ondiicon es u nevento, estouy esperando que algien me nmando una señal (en el aso de la dispositiva estoy esperando al señal de que el buffer no esta lleno - pues m euqwede esperando pq el buffer estaba lleno.)

//en tomar: cond eait n osaldra de alli hasta quye depositvar nio suelte el lock.
// importnter qw pouede venir toro therd  yganar el recurso entonces luego suelt el lock -- se puede emeter en meido y consumir le recurso  por eso es necesario ya q no se garantiza que los que esten en cond wait reciban el reurso 
//(compiten x el lokc-- ahi se quwdan bloquedoss)

//------------------------------------------------------------------------------------

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

		while(num==BUF_SIZE){//buffer lleno
			printf("[producer] waiting...\n");
			pthread_cond_wait(&cond_hay_lugar,&mutex_v);
		}

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