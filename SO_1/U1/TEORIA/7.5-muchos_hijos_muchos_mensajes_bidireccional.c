#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/wait.h>

#define NUM_HIJOS 3
#define MENSAJES_POR_HIJO 3

int main() {
    int hijoAPadre[NUM_HIJOS][2];
    pid_t hijos[NUM_HIJOS];

    // Crear pipes y forkeo de hijos
    for (int i = 0; i < NUM_HIJOS; i++) {
        pipe(hijoAPadre[i]);

        pid_t pid = fork();
        if (pid == 0) {
            // Proceso hijo
            close(hijoAPadre[i][0]); // No leer

            for (int j = 0; j < MENSAJES_POR_HIJO; j++) {
                char mensaje[100];
                snprintf(mensaje, sizeof(mensaje), "Mensaje %d del hijo %d", j + 1, i);
                write(hijoAPadre[i][1], mensaje, strlen(mensaje) + 1);
                sleep(1 + i); // Esperar diferente tiempo según el hijo
            }

            close(hijoAPadre[i][1]);
            exit(0);
        } else {
            hijos[i] = pid;
        }
    }

    // Padre: cerrar extremos de escritura
    for (int i = 0; i < NUM_HIJOS; i++) {
        close(hijoAPadre[i][1]);
    }

    int pipes_abiertos = NUM_HIJOS;
    fd_set readfds;
    int maxfd = 0;
    for (int i = 0; i < NUM_HIJOS; i++) {
        if (hijoAPadre[i][0] > maxfd) maxfd = hijoAPadre[i][0];
    }

    while (pipes_abiertos > 0) {
        FD_ZERO(&readfds);
        for (int i = 0; i < NUM_HIJOS; i++) {
            if (hijoAPadre[i][0] != -1) {
                FD_SET(hijoAPadre[i][0], &readfds);
            }
        }

        int actividad = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (actividad < 0) {
            perror("select");
            break;
        }

        for (int i = 0; i < NUM_HIJOS; i++) {
            if (hijoAPadre[i][0] != -1 && FD_ISSET(hijoAPadre[i][0], &readfds)) {
                char buffer[100];
                int n = read(hijoAPadre[i][0], buffer, sizeof(buffer));
                if (n > 0) {
                    printf("[Padre] Recibí de hijo %d: %s\n", i, buffer);
                } else {
                    // Pipe cerrado
                    close(hijoAPadre[i][0]);
                    hijoAPadre[i][0] = -1;
                    pipes_abiertos--;
                }
            }
        }
    }

    // Esperar hijos
    for (int i = 0; i < NUM_HIJOS; i++) {
        waitpid(hijos[i], NULL, 0);
    }

    printf("[Padre] Todos los mensajes recibidos y procesos finalizados.\n");
    return 0;
}
