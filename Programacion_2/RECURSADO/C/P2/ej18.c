// 4. Cadenas de caracteres
// Ejercicio 18. Escriba una función que reciba una cadena de caracteres y un caracter 
//y devuelva 0 si el caracter esta presente en la cadena y 1 en caso contrario.

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int buscar_char(char string[], char letra){
    for(int x=0;string[x]!='\0';x++){
        if(string[x]==letra){return 0;}
    }
    return 1;
}

void test_buscar_char(void){
    assert(buscar_char("mi mama me ama",'m')==0);
    assert(buscar_char("mi mama me ama",'o')==1);
}

int main(void){
    test_buscar_char(); //TEST

    char cadena[100];
    char letra;

    printf("Ingrese la cadena a analizar: \n");
    fgets(cadena,sizeof(cadena),stdin);
    
    cadena[strcspn(cadena, "\n")] = '\0';// Elimina enter

    printf("Ingrese el char a buscar en la cadena \"%s\" ", cadena);
    scanf(" %c",&letra);

    int result=buscar_char(cadena,letra);

    if(!result){printf("El char \"%c\" se encuentra en la cadena \"%s\" ! \n",letra,cadena);}
    else{printf("No se encontro.");}

    return 0;
}
