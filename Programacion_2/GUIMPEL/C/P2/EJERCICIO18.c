// 4. Cadenas de caracteres

// Ejercicio 18. Escriba una función que reciba una cadena de caracteres y un caracter y de-
// vuelva 0 si el caracter esta presente en la cadena, o 1 en caso contrario

#include <stdio.h>

int aux(char arr[],char carac){
    int bandera=1;
    
    for(int x=0;arr[x]!='\0';x++){
        if(arr[x]==carac){
            bandera=0;
        }
    }
    return bandera;
}

int main(){
    char a[]="abced";
    char f='f';
    char b='b';

    int resultado1=aux(a,f);
    int resultado2=aux(a,b);

    printf("%d\n%d",resultado1,resultado2);
}