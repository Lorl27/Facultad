// Escribí un programa en C que cree 3 hilos, cada uno de los cuales debe incrementar un contador compartido 100.000 veces.
// El contador debe estar protegido con un mutex para evitar condiciones de carrera.
// Al finalizar, el programa debe imprimir el valor final del contador.
// (Recordá inicializar y destruir el mutex correctamente.)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define HILOS_MAX 3
#define CANTIDAD_COMPARTIDA 1000000
#define CONTADOR_ESPERADO  HILOS_MAX* CANTIDAD_COMPARTIDA

pthread_mutex_t mutex_v =PTHREAD_MUTEX_INITIALIZER;

int contador=0;

void* molinete(void * arg){
    for(int x=0;x<CANTIDAD_COMPARTIDA;x++){
        //----lock----
        pthread_mutex_lock(&mutex_v);

        //----region critica---
        contador++;
        //printf("Estoy en cont: %d , en arg: %p",contador,arg);

        //---- unlock ----
        pthread_mutex_unlock(&mutex_v);
    }

    return NULL;
}

int main(){
    pthread_t hilos[HILOS_MAX];

    for(int x=0;x<HILOS_MAX;x++){
        int n =pthread_create(&hilos[x],NULL,molinete,NULL);
        if(n<0){
            perror("Error creando hilos...");
            exit(EXIT_FAILURE);
        }
    }

    //Así, es todo //.
    for(int x=0;x<HILOS_MAX;x++){
        pthread_join(hilos[x],NULL);
    }

    pthread_mutex_destroy(&mutex_v);

    printf("Pase por 3 hilos, 100.000 veces == %d , VALOR ESPERADO: %d ",contador,CONTADOR_ESPERADO);

    return 0;
}