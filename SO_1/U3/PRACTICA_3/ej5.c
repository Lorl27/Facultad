// Ej. 5 (Problema del Barbero, Dijkstra). Una barber´ıa tiene una sala de espera con N sillas y
// un barbero. Si no hay clientes para atender, el barbero se pone a dormir. Si un cliente llega y todas
// las sillas est´an ocupadas, se va. Si el barbero est´a ocupado pero hay sillas disponibles, se sienta en
// una y espera a ser atendido. Si el barbero est´a dormido, despierta al barbero. El cliente y el barbero
// deben ejecutar concurrentemente las funciones me_cortan() y cortando() y al terminar los dos ejecutar
// concurrentemente pagando() y me_pagan().
// Escriba un programa que coordine el comportamiento del barbero y los clientes y expl´ıquelo.

//---------------------

//si no hay clientes->el barbero duerme(espera indefinidamente)
//si hay un cliente nuevo PERO las sillas estan ocupadas: se va
//si el barbero esta ocupado PERO hay sillas libres: el cliente se sienta y espera
//si el babrero duerme, se despieta.


#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>


#define N 3  //Nro sillas
#define CLIENTES 10


sem_t mutex; //proteger var atomica
sem_t clientes; // cuantos clientes esperan

sem_t corte_listo; //podes empezar a cortar
sem_t corte_hecho; //ya cortaste.

sem_t pago_listo;
sem_t pago_hecho;

int clientes_en_espera=0;


void* me_cortan(void* arg){
    int id = (int) (long) arg;

    printf("[Cliente nro %d]: Me cortan el pelo\n",id);

    sleep(1);

    return NULL;

}

void *cortando(void* arg){
    printf("[Barbero]: Estoy cortando.\n");
    sleep(1);
    return NULL;

}

void *pagando(void* arg){
    int id = (int) (long) arg;

    printf("[Cliente %d]: Estoy pagando.\n",id);
    sleep(1);

    return NULL;

}

void *me_pagan(void* arg){
    printf("[Barbero]: Estoy cobrando.\n");
    sleep(1);    

    return NULL;

}

void *cliente(void*arg){
    int id = (int) (long) arg;

    printf("[Cliente nro %d]: Llegue a la barberia\n",id);
  
    sem_wait(&mutex);

    //primero tengo que ver si hay sillas libres
    if(clientes_en_espera>=N){
        printf("[Cliente nro %d]: No hay ninguna silla disponible, nos vemos.\n",id);
        sem_post(&mutex);
        return NULL;
    }

    clientes_en_espera++;
    sem_post(&mutex);

    sem_post(&clientes); //aviso que hay 1+
    sem_wait(&corte_listo); //espero al barbero.

    printf("[Cliente nro %d]: Me voy a cortar el pelo\n",id);
    pthread_t hilo1, hilo2;
    pthread_create(&hilo1, NULL, me_cortan, (void*)(long)id);
    pthread_create(&hilo2, NULL, cortando, NULL);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("[Cliente nro %d]: Ya terminaron de cortarme el pelo.\n",id);
    sem_post(&corte_hecho);     // Avisa al barbero que terminó el corte
    sem_wait(&corte_listo);

    printf("[Cliente nro %d]: Voy a ir a pagar...\n",id);
    pthread_create(&hilo1, NULL, pagando, (void*)(long)id);
    pthread_create(&hilo2, NULL, me_pagan, NULL);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    sem_post(&pago_hecho);      // Avisa al barbero que terminó el pago
    printf("[Cliente nro %d]: Ya termine de pagar. Adiós\n",id);

    sem_wait(&mutex);
    clientes_en_espera--;
    sem_post(&mutex);

    printf("[Cliente %d]: Terminé todo, me voy.\n", id);

    return NULL;

}

void * barbero(void *arg){
    while(1){
        printf("[Barbero]: esperando clientes...\n");
        sem_wait(&clientes);
        printf("Barbero durmiendo...\n");

        sem_post(&corte_listo);
        printf("Barbero despierto...\n");

        sem_wait(&corte_hecho);
        printf("[Barbero]: termine de cortar pelo\n");

        sem_wait(&pago_hecho);
        printf("[Barbero]: terminaron de pagarme. adios");

        printf("[Barbero]: Terminé con un cliente.\n");

    }

    return NULL;
}

int main(){

    pthread_t th_barbero;
    pthread_t th_clientes[CLIENTES];

    sem_init(&mutex,0,1);
    sem_init(&corte_listo,0,0);
    sem_init(&clientes,0,0);
    sem_init(&corte_hecho,0,0);
    sem_init(&pago_listo,0,0);
    sem_init(&pago_hecho,0,0);

    pthread_create(&th_barbero, NULL, barbero, NULL);

    for (int i = 0; i < CLIENTES; i++) {
        pthread_create(&th_clientes[i], NULL, cliente, (void *) (long) i);
        usleep(500000);             // medio segundo entre clientes
    }

    for (int i = 0; i < CLIENTES; i++) {
        pthread_join(th_clientes[i], NULL);
    }

    printf("Todos los clientes fueron atendidos\n");
    return 0;


}