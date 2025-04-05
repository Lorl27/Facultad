// Ej. 7 (Mini Shell). Implemente una versi´on m´ınima de una shell. El programa deber´a esperar l´ıneas
// por entrada est´andar, y al recibir una ejecutar el comando correspondiente, de la misma manera que lo
// hace, por ejemplo, bash.
// a) Implemente una versi´on b´asica que simplemente ejecuta el comando y espera que el mismo termine
// antes de pedir otro. El comando puede especificarse por su path completo o solamente por su nombre
// si se encuentra en alg´un directorio del $PATH (pista: ver execvp()). Ejemplo:
// $ ls
// Makefile shell.c shell
// b) Agregue la posibilidad de pasar argumentos a los comandos, ejemplo:
// $ ls /
// bin boot dev etc ...
// c) Implemente redirecci´on de la salida est´andar. Ahora los comandos pueden tener la forma cmd > file,
// causando que la salida de cmd sea escrita directamente al archivo file. La shell no debe recibir la
// salida y escribirla al archivo, sino que a medida que el comando cmd escriba a su salida est´andar,
// esta salida vaya directamente al archivo.
// Puede usar open("archivo.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644) para abrir (o crear)
// un archivo con permisos usuales. Otras referencias: man 2 open, man 2 close, man 2 dup.
// Ejemplo:1
// $ ls / > salida.txt
// $ cat salida.txt
// bin
// boot
// dev
// ...
// d) Implemente pipes. Modifique el mini shell para que acepte dos comandos por vez. Mediante el uso
// de la funci´on int pipe(int pip[2]), haga que la salida del primer comando sea la entrada del
// segundo.
// La shell debe poder tomar comandos de la forma c1 | c2 causando que la salida del comando c1
// sea dirigida autom´aticamente a la entrada del comando c2. Ning´un proceso espera a que el otro
// termine: ambos inician inmediatamente. Un pipeline puede tener longitud arbitraria (i.e. se debe
// soportar c1 | c2 | c3, etc). Ver tambi´en man 2 pipe. Ejemplo:
// $ ls / | sort -r
// $ var
// usr
// tmp
// ...

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
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

void ejecutar_comando(char* comando){
    char* args[100];
    int i = 0;
    char* token = strtok(comando, " \n");

    while(token != NULL){
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    if(args[0] != NULL && strcmp(args[0], "exit") == 0){
        printf("Saliendo de la shell...\n");
        exit(0);
    }

    pid_t pid = fork();

    if(pid == 0){
        pause();
    }
}

int main(){
    char comando[1024];

    while(1){
        printf("shell> ");
        if(fgets(comando, 1024, stdin) == NULL){
            perror("Error al leer el comando.\n");
            continue;
        }
        ejecutar_comando(comando);
    }
    return 0;
}