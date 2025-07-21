#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Proceso hijo
            execl("/bin/ls", "ls", "-l", NULL);
            perror("execl falló");
            return 1;
        }
    }

    // Proceso padre espera a los 2 hijos
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    printf("Ambos hijos finalizaron.\n");

    return 0;
}
