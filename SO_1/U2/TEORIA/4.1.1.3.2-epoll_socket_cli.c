#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include "8.0-socket_server_configuration.h"

#define MAXMSG 512
#define MAX_EVENTS 2
#define CLI_NOMBRE "./cliente.sock"

int main() {
    int sock_cli;
    struct sockaddr_un srv_name, cli_name;
    socklen_t srv_size;
    ssize_t nbytes;
    char buff[MAXMSG + 1];

    // Crear socket
    sock_cli = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_cli < 0) {
        perror("Falló la creación del socket");
        exit(EXIT_FAILURE);
    }

    // Opcional: identificar al cliente
    cli_name.sun_family = AF_UNIX;
    strncpy(cli_name.sun_path, CLI_NOMBRE, sizeof(cli_name.sun_path));
    unlink(cli_name.sun_path);
    if (bind(sock_cli, (struct sockaddr*)&cli_name, sizeof(cli_name)) < 0) {
        perror("Falló la asignación de nombre");
        exit(EXIT_FAILURE);
    }

    // Conexión al servidor
    srv_name.sun_family = AF_UNIX;
    strncpy(srv_name.sun_path, SRV_NOMBRE, sizeof(srv_name.sun_path));
    srv_size = sizeof(struct sockaddr_un);

    if (connect(sock_cli, (struct sockaddr*)&srv_name, srv_size) < 0) {
        perror("Falló la conexión con el servidor");
        exit(EXIT_FAILURE);
    }

    printf("[DIAG] Conectado a %s\n", SRV_NOMBRE);

    // Crear epoll
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev, events[MAX_EVENTS];

    // Registrar stdin
    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);

    // Registrar socket del cliente
    ev.events = EPOLLIN;
    ev.data.fd = sock_cli;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_cli, &ev);

    // Loop de eventos
    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (n == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n; i++) {
            if (events[i].data.fd == STDIN_FILENO) {
                // Leer del usuario y enviar al servidor
                if (fgets(buff, MAXMSG, stdin) == NULL) continue;
                buff[strcspn(buff, "\n")] = '\0';

                send(sock_cli, buff, strlen(buff), 0);

                if (strcmp(buff, "salir") == 0) {
                    printf("Cerrando cliente por orden del usuario.\n");
                    close(sock_cli);
                    close(epoll_fd);
                    unlink(CLI_NOMBRE);
                    return 0;
                }

            } else if (events[i].data.fd == sock_cli) {
                // Leer del servidor
                nbytes = recv(sock_cli, buff, MAXMSG, 0);
                if (nbytes <= 0) {
                    printf("Servidor desconectado. Cerrando cliente.\n");
                    close(sock_cli);
                    close(epoll_fd);
                    unlink(CLI_NOMBRE);
                    return 0;
                }

                buff[nbytes] = '\0';
                printf("[SERVIDOR] %s\n", buff);
            }
        }
    }

    return 0;
}
