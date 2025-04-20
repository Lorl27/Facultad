#include <pthread.h>
#include <stdio.h>

int contador=0;
int flags[2]={0};
int turno=1;

void* molinete1(void *arg){
    //lock:
    flags[0]=1;
    turno=2;
    while(flags[1]==1 && turno==2){
        ;  //espera...
    }

    //region critica
    contador++;

    //unlock:
    flags[0]=0; //ya no me interesa

    return NULL;
}

void* molinete2(void *arg){
    //lock:
    flags[1]=1;
    turno=1;
    while(flags[0]==1 && turno==1){
        ;  //espera...
    }

    //region critica
    contador++;

    //unlock:
    flags[1]=0; //ya no me interesa

    return NULL;
}

int main(){
    pthread_t m1,m2;

    pthread_create(&m1,NULL,molinete1,NULL);
    pthread_create(&m2,NULL,molinete2,NULL);

    pthread_join(m1,NULL);
    pthread_join(m2,NULL);

    return 0;
}