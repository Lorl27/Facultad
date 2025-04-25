//epoll-lado-servidor

#include <sys/un>
#include <sys/socket>
#include <sys/epoll>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "delete.h"

#define MAX_MSG 1024
#define MAX_EVENTS 10
#define BACKLOG 5

int main(){
    int sock_srv,sock_cli;

    struct sockaddr_un srv_name,cli_name;

    ssize_t nbytes;
    sockeetlen_t cli_size;
    buff[MAX_MSG+1];

    //1 conectar socket con srv:
    sock_srv=socket(AF_UNIX,SOCK_STREAM,0);
    if(sock_srv<0){
        perror("error crear socket"); exit(EXIT_FAILURE);
    }

    //2 nombre al srv:
    srv_name.sun_family=AF_UNIX;
    strncpy(srv_name.sun_path,SRV_NOMBRE,sizeof(srv_name.sun_path));
    unlink(srv_name.sun_path);

    //3 bind name con srv
    if(bind(sock_srv,(struct sockaddr *)&srv_name,sizeof(srv_name))<0){
        perror("error bind socket"); exit(EXIT_FAILURE);
    

    if(listen(sock_srv,BACKLOG)<0){
        perror("error listen socket"); exit(EXIT_FAILURE);
    }

    //4 epoll
    int fde=epoll_create1(0);
    if(fde<0){
        perror("error crear epoll"); exit(EXIT_FAILURE);
    }

    //5 epoll config

    struct epoll_event ev,events[MAX_EVENTS];

    ev.events=EPOLLIN;
    ev.data.fd=sock_srv;

    if(epoll_ctl(fde,EPOLL_CTL_ADD,sock_srv,&ev)<0){
        perror("error epoll ctl"); exit(EXIT_FAILURE);
    }

    printf("[SRV]: esperando conexiones...\n");

    while(1){
        int n=epoll_wait(fde,events,MAX_EVENTS,-1);
        if(n<0){
            perror("error epoll wait"); exit(EXIT_FAILURE);
        }

        for(int x=0;x<n;x++){
            int fdv=events[x].data.fd;

            if(fdv==sock_srv){
                //new conexion:
                cli_size=sizeof(cli_name);
                int cli_new=accept(sock_srv,fdv,(struct sockaddr*)&cli_name,&cli_size);
                if(cli_new<0){
                    perror("error aceptar cliente nuevo"); exit(EXIT_FAILURE);
                }

                printf("[SRV] cliente nro %d aceptado\n",cli_new);

                //epoll + cliente_nuevo
                ev.events=EPOLLIN;
                ev.data.fd=cli_new;
                epoll_ctl(fde,EPOLL_CTL_ADD,cli_new,&ev);
            }
            else{
                //ya hay una.
                nbytes=recv(fdv,buff,MAX_MSG,0);

                if(nbyte<=0){
                    printf("[SRV] cerrando conexion...\n");
                    close(fdv);
                    epoll_ctl(fde,EPOLL_CTL_DEL,fdv,NULL);
                }

                buff[nbytes] = '\0';
                printf("[FD %d] Mensaje: %s", fd, buff);

                //echo:
                send(fdv,buff,nbytes,0);

                if(strncmp(buff,"salir",5)==0){
                    printf("[SRV] cerrando buff...\n");
                    close(fdv);
                    epoll_ctl(fde,EPOLL_CTL_DEL,fdv,NULL);
                }
            }
        }
    }







    close(sock_srv);
    unlink(SRV_NOMRE);
    return 0;
}