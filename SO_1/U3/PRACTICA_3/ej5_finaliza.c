#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TOTAL_CLIENTES 10
#define SILLAS_ESPERA 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_terminados = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_cliente = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_barbero = PTHREAD_COND_INITIALIZER;

int clientes_en_espera = 0;
int cliente_actual = 0;
int clientes_terminados = 0;

void* cliente(void* arg) {
    int id = *(int*)arg;
    free(arg);

    printf("[Cliente nro %d]: Llegue a la barberia\n", id);

    pthread_mutex_lock(&mutex);
    if (clientes_en_espera == SILLAS_ESPERA) {
        printf("[Cliente nro %d]: No hay ninguna silla disponible, nos vemos.\n", id);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex_terminados);
        clientes_terminados++;
        pthread_mutex_unlock(&mutex_terminados);
        return NULL;
    }

    clientes_en_espera++;
    pthread_cond_signal(&cond_cliente); // Despierta al barbero si está dormido
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    while (cliente_actual != id) {
        pthread_cond_wait(&cond_barbero, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    printf("[Cliente nro %d]: Me voy a cortar el pelo\n", id);
    printf("[Cliente nro %d]: Me cortan el pelo\n", id);
    sleep(1); // simulación de corte

    printf("[Cliente nro %d]: Ya terminaron de cortarme el pelo.\n", id);
    printf("[Cliente nro %d]: Voy a ir a pagar...\n", id);

    pthread_mutex_lock(&mutex);
    cliente_actual = -1;
    pthread_cond_signal(&cond_cliente); // Avisar al barbero que puede cobrar
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    printf("[Cliente %d]: Estoy pagando.\n", id);
    pthread_cond_signal(&cond_cliente);
    pthread_mutex_unlock(&mutex);

    sleep(1); // simulación de pago

    pthread_mutex_lock(&mutex);
    printf("[Cliente nro %d]: Ya termine de pagar. Adiós\n", id);
    printf("[Cliente %d]: Terminé todo, me voy.\n", id);
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex_terminados);
    clientes_terminados++;
    pthread_mutex_unlock(&mutex_terminados);

    return NULL;
}

void* barbero(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex_terminados);
        int terminado = clientes_terminados == TOTAL_CLIENTES;
        pthread_mutex_unlock(&mutex_terminados);

        pthread_mutex_lock(&mutex);
        if (terminado && clientes_en_espera == 0 && cliente_actual == 0) {
            pthread_mutex_unlock(&mutex);
            printf("[Barbero]: No quedan más clientes. Me voy.\n");
            break;
        }

        if (clientes_en_espera == 0) {
            printf("[Barbero]: esperando clientes...\n");
            pthread_cond_wait(&cond_cliente, &mutex);
        }

        if (clientes_en_espera > 0 && cliente_actual == 0) {
            clientes_en_espera--;
            cliente_actual = TOTAL_CLIENTES - clientes_terminados;
            printf("Barbero despierto...\n");
            printf("[Barbero]: Estoy cortando.\n");
            pthread_cond_broadcast(&cond_barbero);
            pthread_mutex_unlock(&mutex);
            sleep(1); // cortar
            pthread_mutex_lock(&mutex);
            printf("[Barbero]: termine de cortar pelo\n");

            pthread_cond_wait(&cond_cliente, &mutex); // espera a que el cliente venga a pagar
            printf("[Barbero]: Recibiendo pago...\n");
            pthread_mutex_unlock(&mutex);

            sleep(1); // cobrar

            pthread_mutex_lock(&mutex);
            printf("[Barbero]: Estoy cobrando.\n");
            pthread_mutex_unlock(&mutex);

            sleep(1); // terminar de cobrar

            pthread_mutex_lock(&mutex);
            printf("[Barbero]: terminaron de pagarme. adios");
            printf("[Barbero]: Terminé con un cliente.\n");
            cliente_actual = 0;
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t hilo_barbero;
    pthread_t clientes[TOTAL_CLIENTES];

    pthread_create(&hilo_barbero, NULL, barbero, NULL);

    for (int i = 0; i < TOTAL_CLIENTES; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&clientes[i], NULL, cliente, id);
        usleep(200000); // llegadas espaciadas
    }

    for (int i = 0; i < TOTAL_CLIENTES; i++) {
        pthread_join(clientes[i], NULL);
    }

    pthread_join(hilo_barbero, NULL);
    return 0;
}
