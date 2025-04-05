// 🎯 Objetivo:
// Hacer que el padre escuche a todos los hijos en paralelo y reaccione tan pronto como uno responda, sin esperar a que todos terminen. Esto simula cómo funcionan servidores que manejan múltiples clientes al mismo tiempo.

// 📚 ¿Qué es select()?
// select() te permite esperar múltiples descriptores (por ejemplo, archivos o pipes), y te avisa cuáles tienen datos listos para leer/escribir. Súper útil cuando tenés muchos procesos/hijos que pueden responder en cualquier orden.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <fcntl.h>

#define NUM_HIJOS 3

int main() {
    int padreAHijo[NUM_HIJOS][2];
    int hijoAPadre[NUM_HIJOS][2];
    pid_t hijos[NUM_HIJOS];

    for (int i = 0; i < NUM_HIJOS; i++) {
        pipe(padreAHijo[i]);
        pipe(hijoAPadre[i]);

        pid_t pid = fork();
        if (pid == 0) {
            // Hijo
            close(padreAHijo[i][1]);
            close(hijoAPadre[i][0]);

            char mensaje[100];
            read(padreAHijo[i][0], mensaje, sizeof(mensaje));
            printf("[Hijo %d] Recibí: %s\n", i, mensaje);

            // Simular procesamiento distinto para cada hijo
            sleep(1 + i); // cada hijo responde en distinto momento

            char respuesta[100];
            snprintf(respuesta, sizeof(respuesta), "Soy el hijo %d y terminé!", i);
            write(hijoAPadre[i][1], respuesta, strlen(respuesta) + 1);

            close(padreAHijo[i][0]);
            close(hijoAPadre[i][1]);
            exit(0);
        } else {
            hijos[i] = pid;
        }
    }

    // Padre
    fd_set readfds;
    int maxfd = 0;

    // Cierra extremos que no va a usar
    for (int i = 0; i < NUM_HIJOS; i++) {
        close(padreAHijo[i][0]); // no lee
        close(hijoAPadre[i][1]); // no escribe

        // Enviar mensaje a cada hijo
        char mensaje[100];
        snprintf(mensaje, sizeof(mensaje), "Hola hijo %d, soy papá", i);
        write(padreAHijo[i][1], mensaje, strlen(mensaje) + 1);

        // Determinar el máximo fd (para select)
        if (hijoAPadre[i][0] > maxfd) {
            maxfd = hijoAPadre[i][0];
        }
    }

    int hijos_restantes = NUM_HIJOS;

    while (hijos_restantes > 0) {
        FD_ZERO(&readfds);
        for (int i = 0; i < NUM_HIJOS; i++) {
            FD_SET(hijoAPadre[i][0], &readfds);
        }

        // Esperar respuesta
        int actividad = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (actividad < 0) {
            perror("select");
            exit(1);
        }

        for (int i = 0; i < NUM_HIJOS; i++) {
            if (FD_ISSET(hijoAPadre[i][0], &readfds)) {
                char buffer[100];
                int n = read(hijoAPadre[i][0], buffer, sizeof(buffer));
                if (n > 0) {
                    printf("[Padre] Recibí de hijo %d: %s\n", i, buffer);
                } else {
                    // Cerrado
                    close(hijoAPadre[i][0]);
                }
                hijos_restantes--;
            }
        }
    }

    // Esperar que todos terminen
    for (int i = 0; i < NUM_HIJOS; i++) {
        close(padreAHijo[i][1]);
        waitpid(hijos[i], NULL, 0);
    }

    printf("[Padre] Todos los hijos terminaron.\n");
    return 0;
}
