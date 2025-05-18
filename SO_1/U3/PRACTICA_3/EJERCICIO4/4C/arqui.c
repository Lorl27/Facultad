#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#include "rwlock.h"

// l1 -> () [lectores only] ->> si chau TODOS los lectores->hola escritor
// e1-> nadie mas,solo yo. --> chau

struct rwlock{

    int nro_lectores;  //lectores totales activos
    int nro_lecto_ent;  //lectores en lista de espera
    int nro_escritores;  //escritores totales activos -> 0 v 1
    int nro_escri_ent;  //escritores en lista de espera

    sem_t escritorOK;
    sem_t lectorOK;
    sem_t mutex;

};

struct rwlock *rwlock_init(){
    struct rwlock *rwl=malloc(sizeof(struct rwlock));
    
    sem_init(&rwl->escritorOK, 0, 0); //0: debes esperar hasta que otro hilo haga sem_post
    sem_init(&rwl->lectorOK, 0, 0);
    sem_init(&rwl->mutex, 0, 1);  //semaforo como mutex, 1: esta libre al inicio, lo usaremos para proteces var. compartidas. entonces solo un hilo podra hacer sem_Wait sin bloquearse ==pthread_mutex_t


    rwl->nro_escri_ent = 0;
    rwl->nro_escritores = 0;
    rwl->nro_lecto_ent = 0;
    rwl->nro_lectores = 0;

    return rwl;
}

void rwlock_destroy(struct rwlock *rwl) {
    sem_destroy(&rwl->lectorOK);
    sem_destroy(&rwl->escritorOK);
    sem_destroy(&rwl->mutex);

    free(rwl);
}


void lock_r(struct rwlock *rwl) { 
    sem_wait(&rwl->mutex); //toma el lock → como pthread_mutex_lock

    while(rwl->nro_escritores!=0 || rwl->nro_escri_ent!=0){ //escritor esperando / escribiendo...
        rwl->nro_lecto_ent++;
        sem_post(&rwl->mutex);
        sem_wait(&rwl->lectorOK); // escritor espera a que lector ok
        sem_wait(&rwl->mutex);
        rwl->nro_lecto_ent--;
    }  
    
    rwl->nro_lectores++;
    sem_post(&rwl->mutex); //lector termino de leer --- libera el lock → como pthread_mutex_unlock
}

void unlock_r(struct rwlock *rwl) {
    sem_wait(&rwl->mutex); //espero q el lector haya terminado
    rwl->nro_lectores--;

    if (rwl->nro_lectores == 0 && rwl->nro_escri_ent!=0)
        sem_post(&rwl->escritorOK); //dejo entrar al sig. escritor

    sem_post(&rwl->mutex);  //el lector acabo
}

void lock_w(struct rwlock *rwl) {
    sem_wait(&rwl->mutex);  // escritor espera

    while (rwl->nro_escritores != 0 ||rwl->nro_lectores != 0 ) { //si alguien esta escribiendo/leyendo...
        rwl->nro_escri_ent++;  // lista de espera +1
        sem_post(&rwl->mutex);
        sem_wait(&rwl->escritorOK);  //espera para entrar
        sem_post(&rwl->mutex);
        rwl->nro_escri_ent--;
    }

    // si nadie escribia/leia:
    rwl->nro_escritores++;  //entra
    sem_post(&rwl->mutex);  // envia señal.
}

void unlock_w(struct rwlock *rwl) {
    sem_wait(&rwl->mutex);  //espera q termine el escritor
    rwl->nro_escritores--;

    if (rwl->nro_escri_ent != 0){
        sem_post(&rwl->escritorOK); //dejar pasar al sig. escritor
    }  // si no hay ninguno en la lista espera, lector puede entrar
    else if(rwl->nro_lecto_ent!=0){  // deja pasar a todos los lectores en espera
            for (int i = 0; i < rwl->nro_lecto_ent; i++) {
                sem_post(&rwl->lectorOK);
            }
        }
    }
    sem_post(&rwl->mutex);  //escritor -> entra.
}