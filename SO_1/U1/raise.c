#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

void handler_zero_division(int signum){
    printf("Division por cero. No hagas eso bobi.\n");
    exit(0);
}

int main(){

    pid_t pid=getpid();
   
    void (*signalReturn)(int);
    signalReturn = signal(SIGSTOP,handler_zero_division); //señal q qremos - señal q se va a ejecutar en su lugar (reemplaza su comportamiento)

    raise(SIGSTOP);
    
    printf("OAAAAAAAAAAA %d",pid);
    return 0;
}

//fg in shell == continue command :'(  (el 1ro stoppeado)
//ps -h  procesos q corren + PID
//kill  -CONT pid (cualquiero puedo)