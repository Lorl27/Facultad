#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define BROADCAST_PORT 54321
#define TIMEOUT_SECS 5

void obtener_id_unico(char *nombre) {
    int sock;
    struct sockaddr_in broadcast_addr;
    char mensaje[100];
    fd_set readfds;
    struct timeval timeout;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    int broadcast = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(BROADCAST_PORT);
    broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    snprintf(mensaje, sizeof(mensaje), "NAME_REQUEST %s", nombre);
    sendto(sock, mensaje, strlen(mensaje), 0, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr));

    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);
    timeout.tv_sec = TIMEOUT_SECS;
    timeout.tv_usec = 0;

    if (select(sock + 1, &readfds, NULL, NULL, &timeout) > 0) {
        char buffer[100];
        recv(sock, buffer, sizeof(buffer), 0);
        if (strncmp(buffer, "INVALID_NAME", 12) == 0) {
            printf("Nombre '%s' en uso. Reintente con otro.\n", nombre);
            exit(1);
        }
    }

    close(sock);
    printf("Nombre '%s' adoptado correctamente.\n", nombre);
}