#include <stdio.h>
#include <stdlib.h>

char *copiar_cadena(char *cad, int longitud)
{
    char *a = malloc(sizeof(char) * longitud); //podria fallar la asignacion. no lo contempla
    a = cad;  //ahora 'a' apunta a 'cad, pero perdimos la dir original de 'a'! . MEMORY LEAK
    return a;
}

// la funcion devuelve la cadena modificada en memoria 

int main()
{
    char a[10] = "hola";
    char *b = copiar_cadena(a, 10); //pide mas memoria de la que es necesaria, se rellena con basura
    printf("%s %s\n", a, b);  //hola, hola
    b[0] = 's';
    printf("%s %s\n", a, b);  //sola, sola
    return 0;
}


/* EJERCICIO CORREGIDO:*/

#include <string.h> 

char *copiar_cadena_OK(char *cad, int longitud){
    char *a = malloc(sizeof(char) * longitud); 
    
    if (a == NULL) {
        return NULL; 
    }

    // Copiamos el contenido real, no la flecha del puntero
    strcpy(a, cad); 
    
    return a;
}

int main_OK(){
    char a[10] = "hola";
    char *b = copiar_cadena_OK(a, 10); 

    if (b != NULL) {
        printf("%s %s\n", a, b);  //  hola hola
        b[0] = 's';
        // ahora son cajas separadas en la memoria:
        printf("%s %s\n", a, b);  //  hola sola
        free(b); 
    }
    
    return 0;
}