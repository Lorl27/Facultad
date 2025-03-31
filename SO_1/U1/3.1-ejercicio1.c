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

//-----------------------------------------------

// int main() {
//     pid_t pid = fork();  // Crea un hijo

//     if (pid == 0) {
//         // Código del hijo
//         printf("Soy el hijo, PID: %d\n", getpid());
//         sleep(2);  // Simula trabajo
//         return 42; // Código de salida
//     } else {
//         // Código del padre
//         int status;
//         wait(&status);  // Espera a que el hijo termine

//         if (WIFEXITED(status)) {
//             printf("Hijo terminó con código %d\n", WEXITSTATUS(status));
//         }
//     }
//     return 0;
// }
