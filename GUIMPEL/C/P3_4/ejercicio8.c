//? GESTIÓN DE LA MEMORIA.

//8 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <stdlib.h> 


void ingreseCadena(char* c){
    gets(c);  //agarra todo , incluyendo espacios.
}

int main() {
    char* cadena = malloc(sizeof(char)* 10); //pide espacio para el string
    gets(cadena);
    printf(" %s\n", cadena);
    ingreseCadena(cadena);
    printf(" %s", cadena);  
    return 1;
}


// el código es el mismo , uno usa la var dir y el otro puntero. 
    