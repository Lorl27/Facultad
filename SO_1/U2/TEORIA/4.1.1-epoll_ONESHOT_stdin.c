#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>

#define MAX_EVENTS 5

int main() {
    struct epoll_event event, events[MAX_EVENTS];

    int epoll_fd = epoll_create1(0); //creamos epoll

    event.events = EPOLLIN | EPOLLONESHOT;  //esperamos datos de ENTRADA
    event.data.fd = STDIN_FILENO;  //Monitoreamos el TECLADO

    int s=epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);  //Agrega, modifica o elimina un descriptor de archivo monitoreado
    if(s==-1){
        perror("epoll_ctl error");
        exit(EXIT_FAILURE);
    }

    printf("Esperando entrada por teclado...\n");

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1); //Espera eventos en los descriptores de archivo monitoreados.
        if (n == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n; i++) {
            if (events[i].data.fd == STDIN_FILENO) {
                char buffer[100];
                fgets(buffer, 100, stdin);
                printf("Leído: %s", buffer);

                // Volver a registrar el evento (sino solo pasara 1 vez!)
                event.events = EPOLLIN | EPOLLONESHOT;
                event.data.fd = STDIN_FILENO;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
            }
        }
    }

    close(epoll_fd);
    return 0;
}