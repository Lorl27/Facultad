// Ejercicio 20. Escriba un programa que lea una cadena de caracteres y la imprima al revés.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void al_reves(char array[]){
    int longitud=strlen(array);
    for(int x=longitud-1;x>=0;x--){
        printf("%c",array[x]);
    }
}

int main(void){
    char cadena[100];

    printf("Ingrese la cadena a invertir: ");
    fgets(cadena,sizeof(cadena),stdin);
    cadena[strcspn(cadena,"\n")]='\0'; //sacar new line

    

    printf("la cadena invertida de \"%s\" es: ", cadena);
    al_reves(cadena);

    return 0;
}