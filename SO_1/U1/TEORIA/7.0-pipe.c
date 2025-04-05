#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/un.h>
#include <time.h>

int main(){
    int fd[2];
    pipe(fd);

    char buffer[]="hola mundo";

    pid_t pid=fork();

    if(pid==0){
        printf("Soy el Child.\n");
        close(fd[1]);  //cerramos escritura

        char readBuffer[100];
        int num_read= read(fd[0],readBuffer,sizeof(readBuffer));

        
        if(num_read>0){
            printf("La cadena fue: %s, en carácteres:\n",readBuffer);
        }

        // Imprimir carácter por carácter
            for (int i = 0; i < num_read; i++) {
                printf("Child leyó: %c\t", readBuffer[i]);
            }
            printf("\n");
        
        close(fd[0]); //cerramos lectura.
    }
    else{

        close(fd[0]); //cerramos lectura

        write(fd[1],buffer,strlen(buffer)+1); //incluímos  '\0'

        close(fd[1]); //ceramos escritura

        wait(NULL); //esperamos que termine el child.
    }
    return 0;
}
