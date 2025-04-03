/*

    programa que recibe un nro n , tiene que tener AL MENOS 2 procesos (n>3) 
    EL programa tiene que, que dado n, imprimir de a 3 elementos(nros) (por pantalla) de manera aleatoria
    ej 20: imprime entre 1 y 20 de manera aleatoria : 1,5,8 -- 3,4,7 -- 10,11,6 -- 20,18
    NO puede repetirlos y debo agarrar toda la lista generada por random.

    -- lista + mezcla
    -- agarra lista y la genera

*/

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

#define GROUP_SIZE  2

int* mezclar(int n){

    int *lista=malloc(sizeof(int)*n);

    for(int x = 0; x<n; x++){
        lista[x]=x+1;
    }

    for(int x = 0; x<n; x++){
        int i = rand()%n;  //nro random hasta n
        int temporal = lista[x];
        lista[x] = lista[i];
        lista[i] = temporal;
    }

    return lista;
}


int main(int argc, char* argv[]){

    int n = atoi(argv[1]);

    srand(time(NULL)); //crear semilla random

    char buff[3]; 

    int fd[2];

    pipe(fd);

    int* lista;

    pid_t pid=fork();

    if(pid==0){

        printf("Estamos en el hijo\n");
        close(fd[1]);

       //---

       printf("Imprimire la lista:\t");
       int max=3;
       while(max!=0){
        max=read(fd[0],&buff,4*3); //1 entero=4 bytes
       }

    }else{

        printf("Soy el padre\n");
     
        lista = mezclar(n); // Creamos la lista y la mezclamos

        printf("La lista random es:\n");
        
        for(int x=0;x<n;x++){
            printf("[%d]\t",lista[x]);
        }


        printf("\nYa cree la lista para child. Esperando...\n");

        wait(NULL); //esperamos que el hijo la lea


        //----

        close(fd[0]);

        buff[0]=lista[0];
        buff[1]=lista[1];
        buff[2]=lista[2];
        write(fd[1],buff,12);

        wait(NULL);

        /* La idea es, escribir los  nros de la lista en un "buff"
         para luego pasarselos al hijo, y que éste los vaya leyendo.*/
    }

    return 0;

}