//  g) Que pasa con el uso de memoria de un proceso al realizar fork()? Y exec()?

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

int main(){

    printf("MEMORIA INICIAL");

    pid_t pid=fork();

    printf("MEMORIA DSP DEL FORK");

    char path[]="../txta.txt";
    execl(path,path,NULL);

    printf("MEMORIA DSP DEL EXEC");

    return 0;
}


//* fork() duplica el proceso, pero con Copy-On-Write, por lo que la memoria solo aumenta si el hijo o el padre escriben en ella.

//* exec() reemplaza la memoria del proceso hijo con el nuevo ejecutable, lo que puede aumentar o reducir la memoria usada según el tamaño del nuevo programa.

