#include <fcntl.h>  // Para creat y las banderas
#include <unistd.h> // Para write y close
#include <stdio.h>  // Para perror
#include <stdlib.h> // Para exit

int main() {
    const char *filename = "nuevo_archivo.txt";

    // Crear el archivo con permisos de lectura y escritura para el propietario
    int fd = creat(filename,O_CREAT);
    if (fd == -1) {
        perror("Error al crear el archivo");
        exit(EXIT_FAILURE);
    }

    // Escribir datos en el archivo
    const char *contenido = "Hola, este es un archivo creado con creat.\n";
    ssize_t bytes_escritos = write(fd, contenido, 44);

    if (bytes_escritos == -1) {
        perror("Error al escribir en el archivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Se escribió correctamente el archivo '%s'.\n", filename);

    // Cerrar el archivo
    close(fd);
    return EXIT_SUCCESS;
}