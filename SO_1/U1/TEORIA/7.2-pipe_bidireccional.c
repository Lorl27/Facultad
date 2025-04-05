#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int padreAHijo[2], hijoAPadre[2];
    pipe(padreAHijo);
    pipe(hijoAPadre);

    pid_t pid = fork();

    if (pid == 0) {
        // Hijo
        close(padreAHijo[1]); // No escribe al padre
        close(hijoAPadre[0]); // No lee del padre

        char mensajeRecibido[100];
        read(padreAHijo[0], mensajeRecibido, sizeof(mensajeRecibido));
        printf("[Hijo] Recibí del padre: %s\n", mensajeRecibido);

        char respuesta[] = "Hola papá!";
        write(hijoAPadre[1], respuesta, strlen(respuesta) + 1);

        close(padreAHijo[0]);
        close(hijoAPadre[1]);
        exit(0);

    } else {
        // Padre
        close(padreAHijo[0]); // No lee del pipe que va al hijo
        close(hijoAPadre[1]); // No escribe en el pipe que viene del hijo

        char mensaje[] = "Hola hijo!";
        write(padreAHijo[1], mensaje, strlen(mensaje) + 1);

        char respuesta[100];
        read(hijoAPadre[0], respuesta, sizeof(respuesta));
        printf("[Padre] Recibí del hijo: %s\n", respuesta);

        close(padreAHijo[1]);
        close(hijoAPadre[0]);
        wait(NULL);
    }

    return 0;
}
