#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#include "rwlock.h"

// l1 -> () [lectores only] ->> si chau TODOS los lectores->hola escritor
// e1-> nadie mas,solo yo. --> chau

struct rwlock
{
    int nro_lectores;
    int nro_lecto_ent;
    int nro_escritores;
    int nro_escri_ent;

    sem_t escritorOK;
    sem_t lectorOK;

};

struct rwlock *rwlock_init(){
    struct rwlock *rwl=malloc(sizeof(struct rwlock));
    
    sem_init(&rwl->escritorOK, 0, 1);
    sem_init(&rwl->lectorOK, 0, 1);

    rwl->nro_escri_ent = 0;
    rwl->nro_escritores = 0;
    rwl->nro_lecto_ent = 0;
    rwl->nro_lectores = 0;

    return rwl;
}

void rwlock_destroy(struct rwlock *rwl) {
    sem_destroy(&rwl->lectorOK);
    sem_destroy(&rwl->escritorOK);
    free(rwl);
}


//if escritor -> pása vos mai bro
void lock_r(struct rwlock *rwl) { 

    while(rwl->nro_escritores!=0){
        rwl->nro_escri_ent++;
        sem_wait(&rwl->escritorOK); // lector espera si escritor on
        rwl->nro_escri_ent--;
    }  
    
    rwl->nro_lectores++;
    sem_post(&rwl->lectorOK); //lector termino de leer
}

void unlock_r(struct rwlock *rwl) {
    sem_wait(&rwl->lectorOK); //espero q el lector haya terminado
    rwl->nro_lectores--;
    while (rwl->nro_lectores == 0)
        sem_post(&rwl->escritorOK); //no hay mas adenro

    sem_post(&rwl->lectorOK);  //el lector acabo
}

void lock_w(struct rwlock *rwl) {
    sem_wait(&rwl->lectorOK);  // escritor espera
    while (rwl->nro_escritores != 0) { //si alguien esta escribiendo
        rwl->nro_escri_ent++;  // lista de espera +1
        sem_wait(&rwl->escritorOK);  //espera para entrar
        rwl->nro_escri_ent--;
    }

    // si nadie escribia
    rwl->nro_escritores++;  //entra
    printf("me gano el lector");
        sem_post(&rwl->escritorOK);  // envia señal.
}

void unlock_w(struct rwlock *rwl) {
    sem_wait(&rwl->escritorOK);  //espera q termine el escritor
    rwl->nro_escritores--;
    rwl->nro_escri_ent--;

    while (rwl->nro_escri_ent == 0){
        printf("sem_post(&rwl->lectorOK)");
        sem_post(&rwl->lectorOK);
    }  // i no hay ninguno en la lista espera, lector puede entrar

    printf("sem_post(&rwl->escritorOK)");
    sem_post(&rwl->escritorOK);  //escritor -> entra.
}