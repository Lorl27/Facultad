#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    const char* path="open_read.out";

    //printf("Mi pid es:%d\n",getpid());

    pid_t pid=fork();
    const char *contenido="I want to write something.";
    const char *path2="creacion.txt";

    char contenido2[]="I want to send my dna.";
    
    if(pid==0){
        printf("Soy el hijo\n");
        sleep(5);

        char *token=strtok(contenido2," ");
        while(token!=NULL){
            printf("Dividiendo: %s \n",token);
            token=strtok(NULL, " ");
        }
        
        if(execl(path,path,NULL)<0){
            perror("FALLO EXECL");
            exit(EXIT_FAILURE);
        }
    }else{
        printf("Soy el parent\n");
        int fd=creat(path2,O_CREAT);
        write(fd,contenido,sizeof(contenido));
        printf("escribi: %s en %s \n",contenido,path2);
        wait(NULL);
    }

    printf("Mi pid es:%d\n",getpid());

    return 0;
}