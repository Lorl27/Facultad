#include <fcntl.h>  // Para creat y las banderas
#include <unistd.h> // Para write y close
#include <stdio.h>  // Para perror
#include <stdlib.h> // Para exit

int main() {
    const char *path = "prueba.txt";
    char buffer[1024];

    int fd = open(path,O_RDWR);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

   int n=read(fd,buffer,sizeof(buffer));
   buffer[n]='\0';
   printf("leí: %s\n",buffer);

    // Cerrar el archivo
    close(fd);
    return EXIT_SUCCESS;
}