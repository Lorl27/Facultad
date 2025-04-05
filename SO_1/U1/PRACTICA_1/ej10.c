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


pid_t otro_p; //guardamos a quien le enviamos la señal.

void handler(int signum){
    printf("[%d] recibio SIGURS1\n",getpid());
    kill(otro_p,SIGUSR1); //enviar señal
}

int main(){

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags=0;
    //sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1,&sa,NULL);

    pid_t  pid=fork();

    if(pid==0){
        
        otro_p=getppid(); //parent

        while(1){
            pause();
        }
    }
    else{

        otro_p=pid; //child

        printf("Proceso padre(%d)\n",getpid());
        printf("señal enviada al child [%d].\n",pid);

        kill(pid,SIGUSR1);

        while(1){
            pause();
        }
        
    }


    return 0;

}


/* parent: envia señal
hijo: recibe y manda señal
parent: recibe y manda señal
...abort
*/