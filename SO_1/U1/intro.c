#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//! 2-3-7 (caps)

int main(){
    printf("pid main : %d\n",getpid()); 
    const char* prog="test.out"; 


    execl(prog,prog,NULL); //la funcion ejecuta .exe - nombre.exe (argv[0]) - argms (PISA EL ACUTAL - LUEGO NO SE EJECUTA NADA.)
    return  0;
}

//fork crea un hijo (proceso) copia del parent,
//parent sabe pid child pero al reves no.

