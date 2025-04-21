// ¿Qué es epoll?
// Es un sistema para monitorear múltiples descriptores de archivo (como sockets, archivos o stdin) sin bloquear el programa.

// Sirve para:
// - Saber cuándo un socket tiene datos
// - Saber cuándo hay entrada en stdin
// - Esperar múltiples eventos a la vez
//------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>

#define MAX_EVENTS 5

int main() {
    struct epoll_event event, events[MAX_EVENTS];

    int epoll_fd = epoll_create1(0); //creamos epoll

    event.events = EPOLLIN;  //esperamos datos de ENTRADA
    event.data.fd = STDIN_FILENO;  //Monitoreamos el TECLADO

    int s=epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    if(s==-1){
        perror("epoll_ctl error");
        exit(EXIT_FAILURE);
    }

    printf("Esperando entrada por teclado...\n");

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1); // Bloquea hasta que haya eventos
        if(n==-1){
        perror("epoll_wait");
        exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n; i++) {
            if (events[i].data.fd == STDIN_FILENO) {
                char buffer[100];
                fgets(buffer, 100, stdin);
                printf("Leído: %s", buffer);

                // Si el usuario escribe "exit", terminamos el programa
                if (strcmp(buffer, "exit\n") == 0) {
                    printf("Saliendo...\n");
                    close(epoll_fd);
                    return 0;
                }
            }
        }
    }

    close(epoll_fd);
    return 0;
}
