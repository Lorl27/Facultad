// Ej. 5 (Problema del Barbero, Dijkstra). Una barber´ıa tiene una sala de espera con N sillas y
// un barbero. Si no hay clientes para atender, el barbero se pone a dormir. Si un cliente llega y todas
// las sillas est´an ocupadas, se va. Si el barbero est´a ocupado pero hay sillas disponibles, se sienta en
// una y espera a ser atendido. Si el barbero est´a dormido, despierta al barbero. El cliente y el barbero
// deben ejecutar concurrentemente las funciones me_cortan() y cortando() y al terminar los dos ejecutar
// concurrentemente pagando() y me_pagan().
// Escriba un programa que coordine el comportamiento del barbero y los clientes y expl´ıquelo.

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t estado_sueño_peluquero,peluquero_corte,peluquero_pago;
sem_t mutex;
sem_t estado_cliente,cliente_corte,cliente_pago;

int contador_sillas_ocup=0;

//extra:
int cliente_actual;

#define SILLAS 3
#define MAX_CLI 5 

void *me_cortan(void* arg){
    int id = (int)(size_t)arg;

    printf("[CLI N %d]: Me cortan el pelo.\n",id);
    return NULL;
}

void *cortando(void* arg){
    int id = (int)(size_t)arg;

    printf("[PELU]: Le corto el pelo al cliente [%d].\n",id);
    return NULL;
}

void *me_pagan(void* arg){
    int id = (int)(size_t)arg;

    printf("[PELU]: El cliente [%d] me está pagando.\n",id);
    return NULL;
}

void *pagando(void* arg){
    int id = (int)(size_t)arg;

    printf("[CLI N %d]: Le pago al peluquero.\n",id);
    return NULL;
}

void* peluquero(void * arg){
    int id=arg-(void*)0;

    while(1){
        printf("[PELUQUERO]: durmiendo...\n");
        sem_wait(&estado_cliente); //espero que ingrese un cliente.
        sleep(2); //Simulamos "despertar"
        sem_post(&estado_sueño_peluquero);
        printf("[PELUQUERO]: ya desperté.\n");
        sem_wait(&cliente_corte); //Espero que el cliente se siente a esperar el corte.
        id= cliente_actual;
        cortando((void*)(size_t)id);
        sleep(5); //simulo "corte"
        sem_post(&peluquero_corte); //Envio señal de que ya corte

        sem_wait(&cliente_pago); //Espero que el cliente quiera pagar
        me_pagan((void*)(size_t)id);
        sleep(5); //simulo "pago"
        sem_post(&peluquero_pago); //Envio señal de que ya cobre.

        printf("[PELUQUERO]: ya termine con el cliente nro %d \n",id);


    }

    return NULL;
}


void *cliente(void *arg){
    int id = *(int*)arg;
    free(arg);
    while(1){

        sem_wait(&mutex);
        if(contador_sillas_ocup>=SILLAS){
            printf("[CLIENTE %d]: Todo ocupado... ME VOY\n",id);
            sem_post(&mutex);
            return NULL;
            //sleep(rand() % 5); // espera aleatoria -> vuelven a intentar.
            //continue;
        }

        printf("[CLIENTE %d]: Ingrese a la peluquería...\t Me ire a sentar \n",id);
        contador_sillas_ocup++;
        sem_post(&mutex);

        sem_post(&estado_cliente);
        printf("[CLIENTE %d]: Me sente en la silla =) . \n",id);
        sem_wait(&estado_sueño_peluquero); //Espero que se despierte.
        printf("[CLIENTE %d]: Estoy esperando... \n",id);

        sem_wait(&mutex);
        cliente_actual=id;
        sem_post(&mutex);

        sem_post(&cliente_corte);
        me_cortan((void*)(size_t)id);
        sem_wait(&peluquero_corte);

        printf("[CLIENTE %d]: Me encanto el corte. Ire a pagar \n",id);
        sem_post(&cliente_pago);
        pagando((void*)(size_t)id);
        sem_wait(&peluquero_pago);

        printf("[CLIENTE %d]: Me despido ;)\n",id);
        sem_wait(&mutex);
        contador_sillas_ocup--;
        sem_post(&mutex);

    }

    return NULL; //pthread_exit(NULL); -> forma + controlada de terminas hilos
}
 
int main(){

    sem_init(&estado_sueño_peluquero,0,0); //Arranca durmiendo.
    sem_init(&peluquero_corte,0,0);
    sem_init(&peluquero_pago,0,0);
    sem_init(&mutex,0,1);
    sem_init(&estado_cliente,0,0);
    sem_init(&cliente_corte,0,0);
    sem_init(&cliente_pago,0,0);

    pthread_t pelu,clientes_th[MAX_CLI];
    int x;

    int* id = malloc(sizeof(int));
    *id = 0;
    pthread_create(&pelu, NULL, peluquero, id);


    for(x=0;x<MAX_CLI;x++){
        int* id = malloc(sizeof(int));
        *id = x;
        pthread_create(&clientes_th[x], NULL, cliente, id);
    }

    pthread_join(pelu,NULL); //se ejecuta infinitamente.


    sem_destroy(&estado_sueño_peluquero);
    sem_destroy(&peluquero_corte);
    sem_destroy(&peluquero_pago);
    sem_destroy(&mutex);
    sem_destroy(&estado_cliente);
    sem_destroy(&cliente_corte);
    sem_destroy(&cliente_pago);


    return 0;
}