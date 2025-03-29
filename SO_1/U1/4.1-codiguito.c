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
    int num = 3;
    int cero = 0;
   

    void (*signalReturn)(int);
    signalReturn = signal(SIGFPE,handler_zero_division); //señal q qremos - señal q se va a ejecutar en su lugar (reemplaza su comportamiento)

    int valor = num/cero;

    return 0;
}