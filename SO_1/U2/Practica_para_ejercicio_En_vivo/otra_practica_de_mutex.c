// Escribí un programa en C que cree 2 hilos.
// El hilo A debe imprimir "A" 5 veces,
// y el hilo B debe imprimir "B" 5 veces.
// Queremos que la salida sea intercalada correctamente, así:
// A - B - A - B - A - B - A - B - A - B

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_HILOS 2

pthread_mutex_t mutex_v = PTHREAD_MUTEX_INITIALIZER;

int turno=0;  //0:A -- 1:B


void * molinete1(void *arg){
    for(int x=0;x<5;x++){

        while(turno!=0){
            ;  //espero....
        }

        //---lock--
        pthread_mutex_lock(&mutex_v);

        //---zona critica---
        printf("A\t");
        turno=1;

        //--unlock
        pthread_mutex_unlock(&mutex_v);
    }

    return NULL;
}

void * molinete2(void *arg){
    for(int x=0;x<5;x++){
        while(turno!=1){
            ; //espero...
        }

        //---lock--
        pthread_mutex_lock(&mutex_v);

        //---zona critica---
        printf("B\t");
        turno=0;

        //--unlock
        pthread_mutex_unlock(&mutex_v);
    }

    return NULL;
}

int main(){
    pthread_t hilos[MAX_HILOS];
    
    pthread_create(&hilos[0],NULL,molinete1,NULL);
    pthread_create(&hilos[1],NULL,molinete2,NULL);

    pthread_join(hilos[0],NULL);
    pthread_join(hilos[1],NULL);

    pthread_mutex_destroy(&mutex_v);

    return 0;

}


/** VERSION CON CONDICIONAL MUTEX (NO DADO EN CLASE):
 * 
 *
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_ITER 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int turno = 0; // 0 = A, 1 = B

void* imprimir_A(void* arg) {
    for (int i = 0; i < MAX_ITER; i++) {
        pthread_mutex_lock(&mutex);

        while (turno != 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("A\t");
        turno = 1;
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* imprimir_B(void* arg) {
    for (int i = 0; i < MAX_ITER; i++) {
        pthread_mutex_lock(&mutex);

        while (turno != 1) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("B\t");
        turno = 0;
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t hiloA, hiloB;

    pthread_create(&hiloA, NULL, imprimir_A, NULL);
    pthread_create(&hiloB, NULL, imprimir_B, NULL);

    pthread_join(hiloA, NULL);
    pthread_join(hiloB, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

 * 
 * 
 * 
 * 
 * 
 * 
 */