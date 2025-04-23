#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include "Facultad\SO_1\U1\TEORIA\8.0-socket_server_configuration.h"

#define MAX_EVENTS 10
#define MAXMSG 512
#define BACKLOG 5

int main() {
    int sock_srv, sock_cli;
    struct sockaddr_un srv_name, cli_name;
    socklen_t cli_size;
    ssize_t nbytes;
    char buff[MAXMSG + 1];

    // 1. Crear socket del servidor
    sock_srv = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_srv < 0) {
        perror("Falló la creación del socket");
        exit(EXIT_FAILURE);
    }

    // 2. Configurar dirección (nombre srv)
    srv_name.sun_family = AF_UNIX;
    strncpy(srv_name.sun_path, SRV_NOMBRE, sizeof(srv_name.sun_path));
    unlink(srv_name.sun_path); // asegurarse de que no esté en uso
 
    //3. bind sock srv con sock name
    if (bind(sock_srv, (struct sockaddr *) &srv_name, sizeof(srv_name)) < 0) {
        perror("Falló el bind");
        exit(EXIT_FAILURE);
    }
    
    if (listen(sock_srv, BACKLOG) < 0) {
        perror("Falló el listen");
        exit(EXIT_FAILURE);
    }

    printf("[DIAG] Servidor esperando conexiones (con epoll)\n");

    // 4. Crear epoll
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("Falló epoll_create1");
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev, events[MAX_EVENTS];

    // 5. Registrar el socket del servidor
    ev.events = EPOLLIN;
    ev.data.fd = sock_srv;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_srv, &ev) == -1) {
        perror("fallo epoll_ctl ADD sock_srv");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (n < 0) {
            perror("fallo epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n; i++) {
            int fd = events[i].data.fd;

            if (fd == sock_srv) {
                // Nueva conexión
                cli_size = sizeof(cli_name);
                int nuevo_cli = accept(sock_srv, (struct sockaddr *) &cli_name, &cli_size);
                if (nuevo_cli < 0) {
                    perror("falló accept");
                    continue;
                }

                printf("[DIAG] Nuevo cliente conectado (fd=%d)\n", nuevo_cli);

                // Registrar cliente en epoll
                ev.events = EPOLLIN;
                ev.data.fd = nuevo_cli;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, nuevo_cli, &ev);

            } else {
                // Cliente ya conectado mandó algo
                nbytes = recv(fd, buff, MAXMSG, 0);
                if (nbytes <= 0) {
                    printf("[DIAG] Cliente desconectado (fd=%d)\n", fd);
                    close(fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
                } else {
                    buff[nbytes] = '\0';
                    printf("[FD %d] Mensaje: %s", fd, buff);

                    // Echo de vuelta
                    send(fd, buff, nbytes, 0);

                    // Si manda "salir", cerrar
                    if (strncmp(buff, "salir", 5) == 0) {
                        printf("[DIAG] Cliente pidió salir (fd=%d)\n", fd);
                        close(fd);
                        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
                    }
                }
            }
        }
    }

    close(sock_srv);
    unlink(SRV_NOMBRE);
    return 0;
}
