// Ej. 10 (Signal Pong).
// Hacer un programa que tenga el siguiente comportamiento:
// Luego del fork, el padre env´ıa una se˜nal SIGUSR1 al hijo y entra en un loop infinito.
// El hijo espera en un loop infinito. 
//Ambos (padre e hijo) cuando reciben una se˜nal SIGUSR1 responden lo mismo. (el padre
// al hijo y el hijo al padre).
// ¿Qu´e pasa si cambiamos los loops infinitos por pause()?.
// Usar las funciones signal() y sigaction(). 

//SIGUSR1: Es una señal definida por el usuario para ser usada en programas de aplicación.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>


void handler_child(int signum){
    printf("the señal i have");
}

int main(){
    pid_t  pid=fork();

    if(pid==0){
        struct sigaction sa;

        sa.sa_handler = handler_child;
        //sa.sa_flags = SA_RESTART; // Esta bandera se usa más para reiniciar ciertas llamadas del sistema que se interrumpen por señales, pero no afecta directamente el manejo de señales.
        sa.sa_flags=0;

        sigaction(SIGUSR1,&sa,NULL);

        pause();

    }
    else{
        printf("Proceso padre(%d)\n",getpid());
        printf("señal enviada al child;");
        kill(pid,SIGUSR1);
        
    }
}
