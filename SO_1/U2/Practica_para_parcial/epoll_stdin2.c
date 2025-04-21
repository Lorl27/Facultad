// Escribí un programa en C que use epoll para esperar input desde teclado (stdin).
// Cada vez que el usuario ingrese una línea, el programa debe contar cuántas vocales contiene (mayúsculas o minúsculas).

// Si el usuario escribe "fin", el programa termina.

#include <sys/epoll.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_EVENTS 5

int contar_v(char cadena[]){
    int contador=0;
    char vocales[]={'a','e','i','o','u'};
    for(int x=0;x<strlen(cadena);x++){
        char c = tolower(cadena[x]);
        for(int y=0;y<5;y++){
            if(c==vocales[y]){
                contador++;
            }
        }
    }
    return contador;
}

int main(){
    struct epoll_event ev,events[MAX_EVENTS];
    int fde=epoll_create1(0);
    if(fde==-1){
        perror("fallo crear epoll");
        exit(EXIT_FAILURE);
    }

    ev.events=EPOLLIN|EPOLLONESHOT;
    ev.data.fd=STDIN_FILENO;

    int s=epoll_ctl(fde,EPOLL_CTL_ADD,STDIN_FILENO,&ev);
    if(s==-1){
        perror("fallo ctl epoll");
        exit(EXIT_FAILURE);
    }

    printf("Ingrese algo...\n");

    while(1){
        int n=epoll_wait(fde,events,MAX_EVENTS,-1);
        if(n==-1){
            perror("fallo wait epoll");
            exit(EXIT_FAILURE);
        }

        for(int x=0;x<n;x++){
            if(events[x].data.fd==STDIN_FILENO){
                char buffer[100];
                if(fgets(buffer,sizeof(buffer),stdin)==NULL){
                    perror("ERROR LEYENDO");
                    exit(EXIT_FAILURE);
                }
                buffer[strcspn(buffer,"\n")]='\0';

                if(strcmp(buffer,"fin")==0){
                    printf("Saliendo...");
                    close(fde);
                    return 0;
                }

                printf("[INPUT] %s\n",buffer);
                printf("[VOCALES] %d\n",contar_v(buffer));
                fflush(stdout);

                //restaurar oneshoT:
                ev.events=EPOLLIN|EPOLLONESHOT;
                ev.data.fd=STDIN_FILENO;
                s=epoll_ctl(fde,EPOLL_CTL_MOD,STDIN_FILENO,&ev);
                if(s==-1){
                    perror("fallo ctl epoll");
                    exit(EXIT_FAILURE);
                }

            }
        }
    }

    close(fde);
    return 0;
}