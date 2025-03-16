// Ejercicio 22. Escriba una función que reciba una cadena de caracteres y determine si es un
// pangrama, es decir, si para escribir la línea se utilizaron todos los caracteres del alfabeto.

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int buscar_char(char arr[],char letra){
    for(int x=0;arr[x]!='\0';x++){
        if(tolower(arr[x])==tolower(letra)){
            return 0; //está
        }
    }
    return 1; // no está
}

void test_buscar_char(void){
    assert(buscar_char("domingo",'o')==0);
    assert(buscar_char("domingo",'f')==1);
}


int es_pangrama(char cadena[]){
    //char abc[]="abcdefghijklmnopqrstuvwxyz"; INGLES
    char abc[] = "abcdefghijklmnñopqrstuvwxyzáéíóú"; //ESP
    
    for(int x=0;abc[x]!='\0';x++){
        if(buscar_char(cadena,abc[x])){
            return 1; //no es
        }
    }
    return 0; //es
}

void test_es_pangrama(void){
    //assert(es_pangrama("The quick brown fox jumps over the lazy dog")==0);
    //assert(es_pangrama("Pack my box with five dozen liquor jugs")==0);
    assert(es_pangrama("El veloz murciélago hindú comía feliz cardillo y kiwi")==1);
    assert(es_pangrama("La cigüeña tocaba el saxofón detrás del palenque de paja")==1);
    assert(es_pangrama("domingo de fiesta")==1);
}

int main(void){
    //TESTS:
    test_buscar_char();
    test_es_pangrama();

    char cadena[256];

    printf("Ingrese la palabra ha analizar: ");
    fgets(cadena,sizeof(cadena),stdin);

    cadena[strcspn(cadena,"\n")]='\0';

    int result=es_pangrama(cadena);

    if(result){printf("NO es un pangrama");}
    else{printf(" \"%s\" Es un pangrama!",cadena);}

    return 0;
}

