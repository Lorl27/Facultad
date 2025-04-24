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


// Implemente pipes. Modi que el mini shell para que acepte dos comandos por vez. 
// Mediante el uso
// de la funcion int pipe(int pip[2]), haga que la salida del primer comando sea la entrada del
//  segundo.
//  La shell debe poder tomar comandos de la forma c1 | c2 causando que la salida del comando c1
//  sea dirigida automaticamente a la entrada del comando c2. Ningun proceso espera a que el otro
//  termine: ambos inician inmediatamente.
// Un pipeline puede tener longitud arbitraria (i.e. se debe
//  soportar c1 | c2 | c3, etc).
// Ver tambien man 2 pipe. Ejemplo:
//  $ ls / | sort-r
//  $ var
//  usr
//  tmp
//  ...


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
#define MAX_ARGS 64
#define MAX_SHELL 10

//------------PROTOTIPOS DE FUNCION:

/* Separa por tokens el comando-argumento dado*/
void tokenizacion(char *comando, char **argumentos);

/* Devolverá 1 si es cd/exit y 0 si no. */
int manejar_comandos_internos(char **argumentos); 

/* Ejecuta un único comando, posible > */
void ejecutar_cmd_simple(char *cmd,int redir, char* txt);


/* Maneja el pipelines de múltiples comandos (|) */
void ejecutar_pipes(char *comandos[], int cantidad);
/** Tokenizar comando, detectar >-| y llamar según corresponda */
void procesar_comando(char *comando);

//---------------FUNCIONES

void tokenizacion(char *comando, char **argumentos){
    //? Separaremos comando-argumento:
        int x=0;
        char *token=strtok(comando, " "); //separamos por token.

        while(token!=NULL && x<MAX_ARGS-1){
            argumentos[x++]=token;
            token=strtok(NULL, " "); // Obtiene el siguiente token
    }

        argumentos[x]=NULL; //para el execvp
}

int manejar_comandos_internos(char **argumentos){
    if(argumentos[0]==NULL){ return 1;}

    if(strcmp(argumentos[0],"cd")==0){   //cambio directorio
        if(argumentos[1]==NULL){
            char *home=getenv("HOME");
            if(home==NULL){
                home="/";} //al inicio vamos.
            if(chdir(home)!=0){
                perror("cd");}
        }
        else{
            if(chdir(argumentos[1])!=0){
                perror("cd");}
            }
                return 1;
    }

        if(strcmp(argumentos[0],"exit")==0){ exit(0);}  //para salir
    
    return 0; //no cd-exit found.
}


void ejecutar_cmd_simple(char *cdm,int redir, char* txt){
    char *argumentos[MAX_ARGS];
    tokenizacion(cdm,argumentos);

    if(manejar_comandos_internos(argumentos)){
        return;  //manejamos cd-exit.
    }

    pid_t pid=fork();

    if(pid==0){

        // existe >.
        if(redir && txt!=NULL){
            int fd_o=open(txt,O_CREAT|O_WRONLY|O_TRUNC,0644);

            if(fd_o<0){
                perror("open");
                exit(EXIT_FAILURE);
            }

            dup2(fd_o,STDOUT_FILENO); //redirigimos la salida.
            close(fd_o);
        }

        execvp(argumentos[0],argumentos); //busca el binario usando $PATH
        perror("execvp"); //si llegamos aca, es que fallo  //! IMPORTANTE - SINO puede que el hijo corra inf y se trabe el shell .
        exit(EXIT_FAILURE); //como fallo, nos salimos.
        }
        else{
            wait(NULL);
        }
}


void ejecutar_pipes(char *comandos[], int contador_comandos){
    /* NOTA: 
    pipe(pipes+ i*2) --> pipes[i+2] (lectura) y pipes[i*2+1] (escritura)

    si tengo:  ls | grep txt | wc -l , son 3 comandos pero solo necesito 2 pipes:
    - ls con grep
    - grep con wc

    Entonces se crean n-1 pipes:
    pipes[0] -> read extremo del primer pipe
    pipes[1] -> write extremo del primer pipe
    pipes[2] -> read del segundo pipe
    pipes[3] -> write del segundo pipe

    comando - pipes - elementos en pipes[]
    1           0           0 (caso aparte)
    2           1           2 (pipes[0],pipes[1])
    3           2           4 (pipes[0],pipes[1],pipes[2],pipes[3])
    n           n-1         2*(n-1)

    */
        
    int pipes[2*(contador_comandos-1)]; //[read_fd,write_fd]

    for(int x= 0;x< contador_comandos-1; x++) {
        if (pipe(pipes + x*2) < 0) {  //creación de pipes + verrificación error
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    //para cada comando, creamos un proceso:
    for(int x=0;x<contador_comandos;x++){
        pid_t pid=fork();

        if(pid < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if(pid==0){
            if(x!=0){ //desde el pipe anterior, rederigimos pq no es el primero.
                dup2(pipes[(x-1)*2],STDIN_FILENO);
            }
            if(x!= contador_comandos-1){ //al pipe posterior, rederigimos pq no es el ultimo.
                dup2(pipes[x*2+1],STDOUT_FILENO);
            }
            for(int y=0;y<2*(contador_comandos-1);y++){
                close(pipes[y]); //chau pipes en child!
            }
            char *argumentos[MAX_ARGS];
            tokenizacion(comandos[x],argumentos);
                
            execvp(argumentos[0],argumentos);
            perror("execvp");
            exit(EXIT_FAILURE); //como fallo, nos salimos.
        } //close child
    }// close for
    
    
    //estamos en el padre: 
    for(int x=0;x<2*(contador_comandos-1);x++){
        close(pipes[x]);}
    for(int x=0;x<contador_comandos;x++){
        wait(NULL);}
    
}


void procesar_comando(char *comando){
    //?-----------------  redireccion: (>)
    //En este código, lo que buscamos es si existe: ">" y dónde.
    int redir=0;
    char *txt = NULL;
    char *signo=strchr(comando,'>');  //Buscamos la primera aparición de >

    if(signo!=NULL){
        redir=1;
        *signo='\0'; //en "cmd" se corta el strng.
        signo++; //avanzamos a lo que hay dsp de ">"

        while(*signo==' '){
            signo++; //chau espacios.
        }

        txt=signo; //nuestro comando 
    }

    //?------------------------ Separar pipes con |:
    char *comandos[MAX_SHELL];
    int contador_comandos=0;

    char *token= strtok(comando, "|");

    while(token != NULL && contador_comandos<MAX_SHELL){

        while(*token==' '){
            token++;
        }
        comandos[contador_comandos++]=token;
        token=strtok(NULL, "|");
    }

    if(contador_comandos==1){
        ejecutar_cmd_simple(comandos[0],redir,txt);
    }else{
        ejecutar_pipes(comandos,contador_comandos);
    }

}

//--------------MAIN:

int main(){

    char comando[TAM_MAX];
    
    while(1){
        printf("[SHELL] >\t");
        fflush(stdout); // Muestra el prompt de inmediato.

        if(fgets(comando,TAM_MAX,stdin)==NULL){
            perror("Error al leer el comando");
            break;
        }

        comando[strcspn(comando,"\n")]=0;
        if(strlen(comando)==0){continue;}

        procesar_comando(comando);
    }

    return 0;

}