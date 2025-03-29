#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(){

    pid_t pid=fork();
    int mem;
    if(pid==0){
        printf("soy el hijo   %d: \n",getpid());
        sleep(2);
        printf("i finish\n");
        // exit(0); == return (estado con el que termina) 0=bien
    }
    else{
        pid_t pid_2=getpid();
        printf("pid dad: %d\n",pid_2);
        wait(&mem);
        printf("el child termiono con status: %d\n",mem);
    }

        return 0;
}