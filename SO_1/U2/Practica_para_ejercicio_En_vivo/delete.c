//repaso de todo

//1: EPOLL para stdin!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <string.h>

#define CANT_MAX 5

int main_epoll(){
    struct epoll_event ev,events[CANT_MAX];
    int fde=epoll_create1(0);
    if(fde==-1){
        perror("FALLO EPOLL CREATE");
        exit(EXIT_FAILURE);
    }
    ev.events=EPOLLIN|EPOLLONESHOT;
    ev.data.fd=STDIN_FILENO;

    int s=epoll_ctl(fde,EPOLL_CTL_ADD,STDIN_FILENO,&ev);
    if(s==-1){
        perror("FALLO EPOLL CTL");
        exit(EXIT_FAILURE);
    }
    printf("Ingrese algo aca: \n");

    while(1){
        int n=epoll_wait(fde,events,CANT_MAX,-1);
        if(n==-1){
            perror("FALLO EPOLL WAIT");
            exit(EXIT_FAILURE);
        }

        for(int x=0;x<n;x++){
            if(events[x].data.fd==STDIN_FILENO){
                char buffer[100];
                if(fgets(buffer,sizeof(buffer),stdin)==NULL){
                    perror("ERROR buffer");
                    exit(EXIT_FAILURE);
                }
                buffer[strcspn(buffer,"\n")]='\0';
                

                //cond salida:
                if(strcmp(buffer,"salir")==0){
                    printf("saliendo...\n");
                    close(fde);
                    return 0;
                }

                printf("[input]: %s\n",buffer);
                fflush(stdout);

                //---restaurar:
                
                ev.events=EPOLLIN|EPOLLONESHOT;
                ev.data.fd=STDIN_FILENO;

                if(epoll_ctl(fde,EPOLL_CTL_MOD,STDIN_FILENO,&ev)<0){
                    perror("error");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }


    close(fde);
    return 0;
}


//---------------
//2: Algoritmo de Peterson

#define CONTADOR 100
#define MAX 2
int flags[MAX];  //0: no quiero ir, 1: quiero ir
int turno=0;  //0: mi turno - 1: no lo es.
int contador=0;

void* molinete1(void *arg){
    for(int x=0;x<CONTADOR/2;x++){
        turno=2;
        flags[0]=1;
        while(flags[1]==1 && turno==2){
            ; //espera activa.
        }
        contador++;
        flags[0]=0;
    }

    return NULL;
}

void* molinete2(void *arg){
    for(int x=0;x<CONTADOR/2;x++){
        turno=1;
        flags[1]=1;
        while(flags[0]==1 && turno==1){
            ; //espera activa.
        }
        contador++;
        flags[1]=0;
    }

    return NULL;
}

int main_peterson(){
    pthread_t m1,m2;

    pthread_create(&m1,NULL,molinete1,NULL);
    pthread_create(&m2,NULL,molinete2,NULL);

    pthread_join(m1,NULL);
    pthread_join(m2,NULL);

    printf("[CONTADOR]%d",contador);

    return 0;
}


//------------------
//3: API POSIX MUTEX

#define CONTADOR 100

pthread_mutex_t mutex_v = PTHREAD_MUTEX_INITIALIZER;

int contador=0;

void* molinete1(void *arg){
    for(int x=0;x<CONTADOR/2;x++){
        pthread_mutex_lock(&mutex_v);
        contador++;
        pthread_mutex_unlock(&mutex_v);
    }

    return NULL;
}

void* molinete2(void *arg){
    for(int x=0;x<CONTADOR/2;x++){
        pthread_mutex_lock(&mutex_v);
        contador++;
        pthread_mutex_unlock(&mutex_v);
    }

    return NULL;
}

int main_mutex(){
    pthread_t m1,m2;

    pthread_create(&m1,NULL,molinete1,NULL);
    pthread_create(&m2,NULL,molinete2,NULL);

    pthread_join(m1,NULL);
    pthread_join(m2,NULL);

    printf("[CONTADOR]%d",contador);

    pthread_mutex_destroy(&mutex_v);

    return 0;
}