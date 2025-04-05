#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_NAME "/mi_memoria_compartida"
#define TAM_MEMORIA 1024

int main() {
    // Crear o abrir la memoria compartida
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Ajustar tamaño del segmento
    if (ftruncate(shm_fd, TAM_MEMORIA) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Mapear la memoria
    void *mem = mmap(NULL, TAM_MEMORIA, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Hijo: lee lo que el padre escribió
        sleep(1);  // Dar tiempo al padre
        printf("[Hijo] Leí de la memoria: %s\n", (char *)mem);

        // Desmapear
        munmap(mem, TAM_MEMORIA);
        close(shm_fd);
        exit(0);
    } else {
        // Padre: escribe en la memoria
        strcpy((char *)mem, "Hola desde el padre con shm_open.");
        printf("[Padre] Escribí en la memoria compartida.\n");

        wait(NULL); // Esperar al hijo

        // Limpiar: desmapear, cerrar y eliminar la memoria compartida
        munmap(mem, TAM_MEMORIA);
        close(shm_fd);
        shm_unlink(SHM_NAME);
        printf("[Padre] Memoria compartida liberada.\n");
    }

    return 0;
}
