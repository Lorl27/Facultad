//  Ej. 7 (Mini Shell). Implemente una version mnima de una shell. El programa debera esperar lneas
//  por entrada estandar, y al recibir una ejecutar el comando correspondiente, de la misma manera que lo
//  hace, por ejemplo, bash.

//  a) Implemente una version basica que simplemente ejecuta el comando y espera que el mismo termine
//  antes de pedir otro. El comando puede especi carse por su path completo o solamente por su nombre
//  si se encuentra en algun directorio del $PATH (pista: ver execvp()). Ejemplo:
//  $ ls
//  Makefile shell.c shell

//  b) Agregue la posibilidad de pasar argumentos a los comandos, ejemplo:
//  $ ls /
//  bin boot dev etc ...

//  c) Implemente redireccion de la salida estandar. Ahora los comandos pueden tener la forma cmd > file,
//  causando que la salida de cmd sea escrita directamente al archivo file.
// La shell no debe recibir la
//  salida y escribirla al archivo, sino que a medida que el comando cmd escriba a su salida estandar,
//  esta salida vaya directamente al archivo.
//  Puede usar open("archivo.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644) para abrir (o crear)
//  un archivo con permisos usuales. 

//Otras referencias: man 2 open, man 2 close, man 2 dup.
//  Ejemplo:1
//  $ ls / > salida.txt
//  $ cat salida.txt
//  bin
//  boot
//  dev
//  ...



//ANCHOR -A

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
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/select.h>
#include <sys/mman.h>

#define TAM_MAX 1024

int main(){

    char comando[TAM_MAX];
    
    while(1){
        printf("[SHELL] >\t");
        fflush(stdout); //clear

        if(fgets(comando,TAM_MAX,stdin)==NULL){
            perror("Error al leer el comando");
            break;
        }

        comando[strcspn(comando,"\n")]=0;

        //Separaremos comando-argumento:


        // printf("[SHELL] > %s",comando);
        
        char *argumentos[TAM_MAX/2+1]; //mitad 
        int x=0;
        char *token=strtok(comando, " "); //separamos por token.

        while(token!=NULL){
            argumentos[x++]=token;
            token=strtok(NULL, " ");
        }

        argumentos[x]=NULL; //para el execvp

        if(argumentos[0]==NULL){ continue;}

        if(strcmp(argumentos[0],"exit")==0){ break;}  //para salir

        if(strcmp(argumentos[0],"cd")==0){   //cambio directorio
            if(argumentos[1]==NULL){
                fprintf(stderr,"Dir dont found.\n");
            } 
            else{
                if(chdir(argumentos[1])!=0){
                    perror("cd");
                }
            }
            continue;
        }

        //otros comandos:
        pid_t pid=fork();

        if(pid==0){
            execvp(argumentos[0],argumentos); //busca el binario usando $PATH

            perror("execvp"); //si llegamos aca, es que fallo  //! IMPORTANTE - SINO puede que el hijo corra inf y se trabe el shell .
            exit(EXIT_FAILURE); //como fallo, nos salimos.
        }else{
            wait(NULL);
        }

    }

    return 0;

}