// Ejercicio 21. Escriba una función que reciba una cadena de caracteres y determine si la
// misma es capicúa

#include <stdio.h>
#include <string.h>

int aux(char arr[]){
    
    int longitud = strlen(arr);
    int medio = longitud / 2;

    for(int x=0;x<medio;x++){
        if(arr[x]!=arr[longitud-x-1]){
            return 1; //NO palindromo
        }
    }
    return 0;
}

int main(){
    char arr[]="hola";
    char array[]="radar";

    int resul=aux(arr);
    int resultado=aux(array);

    printf("%d\n%d\n",resul,resultado);
}