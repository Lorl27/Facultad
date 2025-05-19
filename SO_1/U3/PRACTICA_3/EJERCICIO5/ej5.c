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
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 3
#define CLIENTES 10

sem_t estado_barbero; //para ver si está despierto o no
sem_t estado_cliente; //para ver si llego o no

sem_t quiero_pagar_cliente;
sem_t cobro_barbero;

sem_t quiero_corte_cliente;
sem_t corto_barbero;

sem_t mutex;  //para protegeger la var.atomica nro de clientes (fila)

int nro_clientes_espera=0;

void* me_cortan(void *arg){
    int id=  (int) (long) arg;
    printf("[Cliente %d]: Me cortan el pelo\n",id);
    sleep(1);
    return NULL;
}

void* cortando(void *arg){
    int id=  (int) (long) arg;
    printf("Barbero: cortandole el pelo al cliente nro %d]\n",id);
    sleep(1);
    return NULL;
}

void* me_cobran(void *arg){
    int id=  (int) (long) arg;
    printf("[Cliente %d]: Me cobran\n",id);
    sleep(1);
    return NULL;
}

void* cobrando(void *arg){
    int id=  (int) (long) arg;
    printf("Barbero: cobrandole al cliente nro %d]\n",id);
    sleep(1);
    return NULL;
}

void *cliente(void* arg){
    int id=  (int) (long) arg;
    printf("[Cliente %d]: entre a la barberia\n",id);
    sem_wait(&mutex);

    if(nro_clientes_espera>=N){
        printf("[Cliente %d]: La barberia esta llena. Decido irme\n",id);
        sem_post(&mutex);
        return NULL;
    }

    nro_clientes_espera++;
    sem_post(&mutex);

    sem_post(&estado_cliente);  //avise que llegue
    printf("[Cliente %d]: Estoy esperando al barbero...\n",id);
    sem_wait(&estado_barbero); //espero que se despierte o se desocupe.

    sem_post(&quiero_corte_cliente);
    printf("[Cliente %d]: Me voy a cortar el pelo\n",id);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,me_cortan,(void*)(long)id);
    pthread_create(&t2,NULL,cortando,(void*)(long)id);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_wait(&corto_barbero); //espero que me lo terminen de cortar.

    sem_post(&quiero_pagar_cliente); ///aviso que quiero pagar
    printf("[Cliente %d]: Quiero pagar...\n",id);
    pthread_create(&t1,NULL,me_cobran,(void*)(long)id);
    pthread_create(&t2,NULL,cobrando,(void*)(long)id);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_wait(&cobro_barbero); //espero que me terminen de cobrar.

    sem_wait(&mutex);
    nro_clientes_espera--;
    sem_post(&mutex);

    printf("[Cliente %d]: Listo! ya termine. Nos vemos\n\n",id);


    return NULL;
}

void * barbero(void *arg){
    while(1){   
        printf("[BARBERO]: durmiendo...\n");
        sem_wait(&estado_cliente); //espero q llegue uno para despertarme
        printf("[BARBERO]: estoy despertando...\n");
        sleep(1);
        sem_post(&estado_barbero);
        printf("[BARBERO]: ya desperte.\n");

        sem_wait(&quiero_corte_cliente);
        printf("[BARBERO]: Cortando pelo...\n");
        sleep(2);
        sem_post(&corto_barbero);
        printf("[BARBERO]: Listo pelo.\n");

        sem_wait(&quiero_pagar_cliente);
        printf("[BARBERO]: Cobrando...\n");
        sleep(2);
        sem_post(&cobro_barbero);
        printf("[BARBERO]: Listo cobro.\n");

        printf("[Barbero] termine con un cliente.\n\n");

    }
    return NULL;
}

int main(){
    sem_init(&estado_barbero,0,0);
    sem_init(&estado_cliente,0,0);
    sem_init(&quiero_pagar_cliente,0,0);
    sem_init(&cobro_barbero,0,0);
    sem_init(&quiero_corte_cliente,0,0);
    sem_init(&corto_barbero,0,0);
    sem_init(&mutex,0,1);

    pthread_t hilo_barbero;
    pthread_t hilo_clientes[CLIENTES];

    pthread_create(&hilo_barbero,NULL,barbero,NULL);

    for(int x=0;x<CLIENTES;x++){
        pthread_create(&hilo_clientes[x],NULL,cliente,(void *) (long) x);
        usleep(500000);  //0.5s
    }

     for(int x=0;x<CLIENTES;x++){
        pthread_join(hilo_clientes[x],NULL);
    }

    pthread_join(hilo_barbero,NULL);

    printf("\nYa se atendio a todos. \n");

    return 0;
}