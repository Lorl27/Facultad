// Escribí un programa en C que cree 6 hilos:

// 3 hilos deben sumar 1 a una variable global 100.000 veces cada uno.

// 3 hilos deben restar 1 a la misma variable global 100.000 veces cada uno.

// La variable debe estar protegida con un mutex para evitar condiciones de carrera.
// Al finalizar, el programa debe imprimir el valor final de la variable 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define HILOS_MAX 6
#define PASOS 100000
int global=0;

#define VALOR_ESPERADO (HILOS_MAX/2)*(global+100000) + (HILOS_MAX/2)*(global-100000)

pthread_mutex_t mutex_v = PTHREAD_MUTEX_INITIALIZER;

void* sumar(void *arg){
    for(int x=0;x<PASOS;x++){
        //---lock
        pthread_mutex_lock(&mutex_v);

        //--zona critica--
        global++;

        //unlock----
        pthread_mutex_unlock(&mutex_v);
    }

    return NULL;
}

void* restar(void *arg){
    for(int x=0;x<PASOS;x++){
        //---lock
        pthread_mutex_lock(&mutex_v);

        //--zona critica--
        global--;

        //unlock----
        pthread_mutex_unlock(&mutex_v);
    }

    return NULL;
}

int main(){
    pthread_t hilos[HILOS_MAX];

    for(int x=0;x<HILOS_MAX/2;x++){
        pthread_create(&hilos[x],NULL,sumar,NULL);
    }

    for(int x=0;x<HILOS_MAX/2;x++){
        pthread_create(&hilos[x],NULL,restar,NULL);
    }

    for(int x=0;x<HILOS_MAX;x++){
        pthread_join(hilos[x],NULL);
    }

    pthread_mutex_destroy(&mutex_v);

    printf("VAR GLOBAL= %d [VAR ESPERADO: %d]\n",global,VALOR_ESPERADO);

    return 0;
}