#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rwlock.h"

#define sleep(n) usleep(1000*(n))


#define M 5  // lector
#define N 5  // escritor
#define ARRLEN 10240

struct rwlock *rwl;

int arr[ARRLEN];

void *escritor(void *arg) {
    int i = 1;
    int num = arg - (void *)0;
    while (1) {
        sleep(num % 3);

        printf("--->Entro escritor %d\n",num);
        lock_w(rwl);
        printf("[ESCRITOR %d]: tome el lock. me preparo \n",num);

        printf("Escritor %d escribiendo\n", num);
        for (i = 0; i < ARRLEN; i++)
            arr[i] = num;

        unlock_w(rwl);
        printf("[ESCRITOR %d]: He terminado de escribir. \n",num);
    }

    return NULL;
}

void *lector(void *arg) {
    int v, i = 1;
    int num = arg - (void *)0;
    while (1) {
        sleep(num % 3);

        printf("-->Entro lector %d -\n",num);
        lock_r(rwl);
        printf("[LECTOR] %d: tome el lock. me preparo\n", num);

        v = arr[0];
        for (i = 1; i < ARRLEN; i++) {
            if (arr[i] != v)
                break;
        }
        if (i < ARRLEN)
            printf("Lector %d, error de lectura\n", num);
        else
            printf("Lector %d, dato %d\n", num, v);

        printf("[LECTOR %d]: termine de leer\n",num);
        unlock_r(rwl);
    }

    return NULL;
}

int main() {
    pthread_t lectores[M], escritores[N];
    int i;

    rwl = rwlock_init();

    for (i = 0; i < M; i++)
        pthread_create(&lectores[i], NULL, lector, i + (void *)0);

    for (i = 0; i < N; i++)
        pthread_create(&escritores[i], NULL, escritor, i + (void *)0);


    pthread_join(lectores[0], NULL); /* Espera para siempre */

    printf("Se rompio todo.\n");

    rwlock_destroy(rwl);
    return 0;
}