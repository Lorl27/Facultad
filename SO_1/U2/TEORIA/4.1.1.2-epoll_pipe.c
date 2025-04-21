#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENTS 2

int pipe1[2];
int pipe2[2];

void* escribir_pipe1(void* arg) {
    while (1) {
        write(pipe1[1], "Mensaje desde pipe1\n", 21);
        sleep(2);
    }
    return NULL;
}

void* escribir_pipe2(void* arg) {
    while (1) {
        write(pipe2[1], "Mensaje desde pipe2\n", 21);
        sleep(3);
    }
    return NULL;
}

int main() {
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Error creando pipes");
        exit(EXIT_FAILURE);
    }

    // Crear hilos que escriben a los pipes
    pthread_t hilo1, hilo2;
    pthread_create(&hilo1, NULL, escribir_pipe1, NULL);
    pthread_create(&hilo2, NULL, escribir_pipe2, NULL);

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("Error creando epoll");
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev, events[MAX_EVENTS];

    ev.events = EPOLLIN;
    ev.data.fd = pipe1[0];
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pipe1[0], &ev);

    ev.events = EPOLLIN;
    ev.data.fd = pipe2[0];
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pipe2[0], &ev);

    printf("Escuchando datos en los pipes...\n");

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (n == -1) {
            perror("Error en epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n; i++) {
            char buffer[128];
            int bytes = read(events[i].data.fd, buffer, sizeof(buffer) - 1);
            buffer[bytes] = '\0';

            if (events[i].data.fd == pipe1[0]) {
                printf("[PIPE 1] %s", buffer);
            } else if (events[i].data.fd == pipe2[0]) {
                printf("[PIPE 2] %s", buffer);
            }
        }
    }

    close(epoll_fd);
    return 0;
}
