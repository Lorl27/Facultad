#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex_v= PTHREAD_MUTEX_INITIALIZER;
int contador=0;

void* molinete(void * arg){
    //lock:
    pthread_mutex_lock(&mutex_v);

    //region critica:
    contador++;

    //unlock:
    pthread_mutex_unlock(&mutex_v);

    return NULL;
}

int main(){
    pthread_t m1,m2;

    pthread_create(&m1,NULL,molinete,NULL);
    pthread_create(&m2,NULL,molinete,NULL);

    pthread_join(m1,NULL);
    pthread_join(m2,NULL);

    pthread_mutex_destroy(&mutex_v);

    return 0;
}