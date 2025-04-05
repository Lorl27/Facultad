// 🎯 Objetivo:
// Usar mmap() para crear una región de memoria que puedan compartir padre e hijo después del fork().

// El padre escribe un mensaje.

// El hijo lo lee desde esa misma memoria.

// 🧠 ¿Por qué mmap()?
// Más simple que shmget() + shmat() + ftok().

// No requiere claves ni eliminación manual de recursos.

// Muy útil en programas modernos, especialmente cuando se necesita memoria compartida temporal.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define TAM_MEMORIA 1024

int main() {
    // Crear memoria compartida anónima (no respaldada por archivo)
    void *mem = mmap(NULL, TAM_MEMORIA, PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Hijo: lee lo que el padre escribió
        sleep(1);  // Esperar a que el padre escriba
        printf("[Hijo] Leí de la memoria: %s\n", (char *)mem);
        munmap(mem, TAM_MEMORIA);
        exit(0);
    } else {
        // Padre: escribe el mensaje
        strcpy((char *)mem, "Hola desde el padre con mmap.");
        printf("[Padre] Escribí en la memoria compartida.\n");
        wait(NULL);
        munmap(mem, TAM_MEMORIA);
        printf("[Padre] Memoria compartida liberada.\n");
    }

    return 0;
}
