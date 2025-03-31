#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler_child(int sig){
    printf("Me mandaron la señal\n");
}

int main(){

    pid_t pid=fork();

    if(pid==0){
        struct sigaction sa;
        sa.sa_handler = handler_child;
        //sa.sa_flags = SA_RESTART; // Esta bandera se usa más para reiniciar ciertas llamadas del sistema que se interrumpen por señales, pero no afecta directamente el manejo de señales.
        sa.sa_flags=0;
        sigaction(SIGINT,&sa,NULL);

        printf("Proceso hijo(PID: %d) esperando señales...\n",getpid());
        pause(); // Espera señales, evitando que termine inmediatamente.
    }
    else{
        printf("Proceso padre(%d)\n",getpid());
        sleep(3);
        kill(pid,SIGINT); //enviamos SIGINT 
        wait(NULL); //Esperamos q child finish
    }

    printf("Quién llego: %d\n",getpid());
    return 0;
}
