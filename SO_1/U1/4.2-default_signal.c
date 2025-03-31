#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

void manejador(int sig) {
    printf("Señal %d recibida. Restableciendo comportamiento predeterminado.\n", sig);
    // Restauramos el comportamiento predeterminado para SIGINT
    signal(SIGINT, SIG_DFL);
    printf("¡Ahora Ctrl+C terminará el programa!\n");
}

int main() {
    // Registra el manejador para la señal SIGINT (Ctrl+C)
    if (signal(SIGINT, manejador) == SIG_ERR) {
        printf("Error al establecer el manejador de señales.\n");
        return 1;
    }

    while (1) {
        printf("Esperando una señal... Presiona Ctrl+C para probar.\n");
        sleep(1);
    }

    return 0;
}
