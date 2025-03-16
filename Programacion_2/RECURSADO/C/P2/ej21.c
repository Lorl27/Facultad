// Ejercicio 21. Escriba una función que reciba una cadena de caracteres y determine si la
// misma es capicua.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int es_capicua(char cadena[]){
    int longitud=strlen(cadena);
    for(int x=0, y=longitud-1; x<y; x++, y--){
            if(cadena[x]!=cadena[y]){
                return 1; //no capi
            }
        }
    return 0; //capi
}

void test_es_capicua(void){
    assert(es_capicua("hola")==1);
    assert(es_capicua("hola aloh")==0);
    assert(es_capicua("ala")==0);
}

int main(void){
    test_es_capicua(); //TEST

    char array[100];

    printf("Ingrese la cadena a la cual desea revisar: ");

    fgets(array,sizeof(array),stdin);

    array[strcspn(array,"\n")]='\0'; //elimina tab

    int resultado=es_capicua(array);

    if(resultado){printf("NO es capicua! \n");}
    else{printf("CAPICUAAA");}

    return 0;
}
