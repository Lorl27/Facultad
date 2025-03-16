// Ejercicio 19. Escriba una función que reciba una cadena de caracteres 
//y un caracter y devuelva la cantidad de apariciones del caracter en la cadena.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int aparaciones(char cadena[], char letra){
    int contador=0;
    for(int x=0;cadena[x]!='\0';x++){
        if(cadena[x]==letra){
            contador++;
        }
    }
    return contador;
}

void test_apariciones(void){
    assert(aparaciones("hola mama",'m')==2);
    assert(aparaciones("hola mama",'o')==1);
    assert(aparaciones("hola mama",'f')==0);
}

int main(void){
    test_apariciones(); //TEST

    char string[100];
    char caracter;

    printf("Ingrese la cadena a analizar: ");
    fgets(string,sizeof(string),stdin);
    string[strcspn(string,"\n")]='\0'; //Elimina new line

    printf("Ingrese el caracter a buscar en \"%s\" ",string);
    scanf(" %c",&caracter);

    int result=aparaciones(string,caracter);

    if(result!=0){printf("El caracter \"%c\" en la cadena \"%s\" se encontro %d veces! \n",caracter,string,result);}
    else{printf("Ese caracter no se encuentra en la cadena.");}

    return 0;
}