#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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
            // Proceso hijo
            close(padreAHijo[i][1]); // El hijo no escribe en este pipe
            close(hijoAPadre[i][0]); // El hijo no lee en este pipe

            // Leer mensaje del padre
            char mensaje[100];
            read(padreAHijo[i][0], mensaje, sizeof(mensaje));
            printf("[Hijo %d] Recibí: %s\n", i, mensaje);

            // Preparar y enviar respuesta
            char respuesta[100];
            snprintf(respuesta, sizeof(respuesta), "Hola papá, soy el hijo %d", i);
            write(hijoAPadre[i][1], respuesta, strlen(respuesta) + 1);

            close(padreAHijo[i][0]);
            close(hijoAPadre[i][1]);
            exit(0);
        } else {
            hijos[i] = pid;
        }
    }

    // Proceso padre
    for (int i = 0; i < NUM_HIJOS; i++) {
        close(padreAHijo[i][0]); // No lee en este pipe
        close(hijoAPadre[i][1]); // No escribe en este pipe

        // Enviar mensaje a cada hijo
        char mensaje[100];
        snprintf(mensaje, sizeof(mensaje), "Hola hijo %d, soy papá", i);
        write(padreAHijo[i][1], mensaje, strlen(mensaje) + 1);
    }

    // Leer respuestas de los hijos
    for (int i = 0; i < NUM_HIJOS; i++) {
        char respuesta[100];
        read(hijoAPadre[i][0], respuesta, sizeof(respuesta));
        printf("[Padre] Recibí del hijo %d: %s\n", i, respuesta);

        close(padreAHijo[i][1]);
        close(hijoAPadre[i][0]);
    }

    // Esperar a todos los hijos
    for (int i = 0; i < NUM_HIJOS; i++) {
        wait(NULL);
    }

    printf("[Padre] Todos los hijos terminaron.\n");
    return 0;
}
