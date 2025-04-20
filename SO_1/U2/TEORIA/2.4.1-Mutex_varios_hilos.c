#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define CANT_HILOS 10
#define INCREMENTOS_POR_HILO 10000

pthread_mutex_t mutex_v = PTHREAD_MUTEX_INITIALIZER;
int contador = 0;

void* molinete(void *arg) {
    for (int i = 0; i < INCREMENTOS_POR_HILO; i++) {
        pthread_mutex_lock(&mutex_v);

        contador++;

        pthread_mutex_unlock(&mutex_v);
    }

    return NULL;
}

int main() {
    pthread_t hilos[CANT_HILOS];

    for (int i = 0; i < CANT_HILOS; i++) {
        if (pthread_create(&hilos[i], NULL, molinete, NULL) != 0) {
            perror("Error creando hilo");
            exit(1);
        }
    }

    for (int i = 0; i < CANT_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    pthread_mutex_destroy(&mutex_v);

    printf("Valor final del contador: %d (esperado: %d)\n", contador, CANT_HILOS * INCREMENTOS_POR_HILO);

    return 0;
}
