// Escribí un programa que use epoll para esperar input desde teclado (stdin).
// El programa debe imprimir cuántos caracteres leídos tiene cada línea.
// Cuando el usuario escribe "salir", el programa debe finalizar.

#include <stdio.h>
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_EVENTS 5

int main(){
    struct epoll_event ev,events[MAX_EVENTS];

    int fde=epoll_create1(0);
    if(fde==-1){
        perror("fallo crear epoll1");
        exit(EXIT_FAILURE);
    }
    ev.events=EPOLLIN | EPOLLONESHOT;
    ev.data.fd=STDIN_FILENO;

    int s=epoll_ctl(fde,EPOLL_CTL_ADD,STDIN_FILENO,&ev);
    if(s==-1){
        perror("FALLO EPOLL_CTL");
        exit(EXIT_FAILURE);
    }

    printf("Ingresa algo, salir para finalizar. \n");
    
    while(1){
        int n=epoll_wait(fde,events,MAX_EVENTS,-1);
        if(n<0){
            perror("FALLO EPOLL_WAIT");
            exit(EXIT_FAILURE);
        }

        for(int x=0;x<n;x++){
            if(events[x].data.fd==STDIN_FILENO){
                char buffer[100];

                if(fgets(buffer,sizeof(buffer),stdin)==NULL){
                    perror("error leyendo.");
                    continue;
                }



                buffer[strcspn(buffer, "\n")] = '\0';
                
                //cond de salir
                if(strcmp(buffer,"salir")==0){
                    printf("salinedo..\n");
                    close(fde);
                    return 0;
                } 

                printf("[INPUT] %s\n",buffer);
                printf("[TOTAL CARACTERES] %ld \n",strlen(buffer));
                fflush(stdout); // Fuerza a imprimir en orden si hay buffering

        
                //restaurar
                ev.events=EPOLLIN|EPOLLONESHOT;
                ev.data.fd=STDIN_FILENO;
                if(epoll_ctl(fde,EPOLL_CTL_MOD,STDIN_FILENO,&ev)<0){
                    perror("fallo epoll_ctl");
                    exit(EXIT_FAILURE);
                }

        }   }
    }
    
    close(fde);
    return 0;    
}