// Escribí un programa que simule un proceso de producción-control, con:

// 1 hilo que produce un recurso (sumando 1 a una variable global)

// 1 hilo que consume (resta 1 a la misma variable)

// El recurso debe mantenerse entre 0 y 10 (es decir, no podés producir si hay más de 10, y no podés consumir si hay 0).

// Usá mutex y lógica propia para asegurar que:

// El productor espere activamente si ya hay 10 recursos.

// El consumidor espere activamente si no hay recursos disponibles.

// Ambos deben repetir el proceso 100 veces.
// Al final, imprimí el valor final del recurso y un mensaje que indique si el comportamiento fue correcto.

#include <stdio.h>
#include <pthread.h>

#define repeticion 100

int recurso=0;

pthread_mutex_t mutex_v = PTHREAD_MUTEX_INITIALIZER;

void* producir_recurso(void *arg){
    for(int x=0;x<repeticion;x++){
        int bandera=0;
        while(!bandera){
        //--lock
        pthread_mutex_lock(&mutex_v);

        //--region critica---
        if(recurso<10){ //espera...
            recurso++;
            bandera=1;
        }
        
        //unlock ---
        pthread_mutex_unlock(&mutex_v);
        }
    }

    return NULL;
}

void* consumir_recurso(void *arg){
    for(int x=0;x<repeticion;x++){
        int bandera=0;
        while(!bandera){
        //--lock
        pthread_mutex_lock(&mutex_v);

        //--region critica---
        if(recurso>0){ //espera...
            recurso--;
            bandera=1;
        }
        
        //unlock ---
        pthread_mutex_unlock(&mutex_v);
        }
    }

    return NULL;
}

int main(){
    pthread_t hilo1,hilo2;

    pthread_create(&hilo1,NULL,producir_recurso,NULL);
    pthread_create(&hilo2,NULL,consumir_recurso,NULL);

    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);

    pthread_mutex_destroy(&mutex_v);

    printf("El recurso quedo en el nro: %d\n",recurso);

    if(recurso<=10 && recurso>=0){
        printf("El recurso esta en el rango [0,10] correcto =)\n");
    }else{
        printf("Quedo fuera del rango...\n");
    }

    return 0;
}