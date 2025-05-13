#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


#define M 5  //lector
#define N 5  //escritor uwu
#define ARRLEN 10240

pthread_mutex_t mutex_v=PTHREAD_MUTEX_INITIALIZER;
sem_t lector_libre_sem;
sem_t lector_ocupado_sem;

int arr[ARRLEN];

void *escritor(void *arg)
{
    int i;
    int num = arg - (void *)0;
    while (1)
    {
        sem_wait(&lector_libre_sem);
		pthread_mutex_lock(&mutex_v);

        sleep(i%3);
        printf("Escritor %d escribiendo\n", num);
        for (i = 0; i < ARRLEN; i++)
            arr[i] = num;

        pthread_mutex_unlock(&mutex_v);
        sem_post(&lector_ocupado_sem); 
    }

    return NULL;
}

void *lector(void *arg)
{
    int v, i;
    int num = arg - (void *)0;
    while (1)
    {

        sem_wait(&lector_ocupado_sem);  //down
		pthread_mutex_lock(&mutex_v);
        sleep(i%3);
        v = arr[0];
        for (i = 1; i < ARRLEN; i++)
        {
            if (arr[i] != v)
                break;
        }
        if (i < ARRLEN)
            printf("Lector %d, error de lectura\n", num);
        else
            printf("Lector %d, dato %d\n", num, v);

        
		pthread_mutex_unlock(&mutex_v);
        sem_post(&lector_libre_sem);
    }

    return NULL;
}

int main()
{
    pthread_t lectores[M], escritores[N];
    int i;
    sem_init(&lector_ocupado_sem,0,M); //para threads:no compartido en dif proceos.
    sem_init(&lector_libre_sem,0,0); 

    for (i = 0; i < M; i++)
        pthread_create(&lectores[i], NULL, lector, i + (void *)0);

    for (i = 0; i < N; i++)
        pthread_create(&escritores[i], NULL, escritor, i + (void *)0);
    pthread_join(lectores[0], NULL); /* Espera para siempre */

    sem_destroy(&lector_libre_sem);
    sem_destroy(&lector_ocupado_sem);
    return 0;
}