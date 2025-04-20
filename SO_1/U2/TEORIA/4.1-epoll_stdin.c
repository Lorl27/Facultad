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
    int epoll_fd = epoll_create1(0);

    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    printf("Esperando entrada por teclado...\n");

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        for (int i = 0; i < n; i++) {
            if (events[i].data.fd == STDIN_FILENO) {
                char buffer[100];
                fgets(buffer, 100, stdin);
                printf("Leído: %s", buffer);
            }
        }
    }

    close(epoll_fd);
    return 0;
}
