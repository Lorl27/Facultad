// CREA UNA DEFINICION PROPIA DE strcpy(s1,s2) 
//"s2 va a s1" - DESTINO:s1 , ORIGEN:s2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void copiar_strings(char s1[], char s2[]){
    
    for(int x=0;s2[x]!='\0';x++){
        s1[x]=s2[x];
        s1[x+1]='\0';
    }
    
}


int main(void){
    char cadena_origen[100];
    char cadena_destino[100];

    
    printf("Ingrese la cadena A COPIAR: ");
    fgets(cadena_origen,sizeof(cadena_origen),stdin);

    copiar_strings(cadena_destino,cadena_origen);

    printf("Cuando copiamos obtenemos: %s \n", cadena_destino);

    //clean data:
    strcpy(cadena_destino, "");
    strcpy(cadena_destino,cadena_origen);
    printf("Cuando copiamos obtenemos: %s \n", cadena_destino);

    return 0;
}