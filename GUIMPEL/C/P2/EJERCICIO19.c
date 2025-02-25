// Ejercicio 19. Escriba una función que reciba una cadena de caracteres y un caracter y de-
// vuelva la cantidad de apariciones del caracter en la cadena dada

#include <stdio.h>

int aux(char arr[],char carac){
    int ap=0;
    for(int x=0;arr[x]!='\0';x++){
        if(arr[x]==carac){
            ap+=1;
        }
    }
    return ap;
}

int main(){
    char ar1[]="amelia";
    char a='a';
    char b='b';

    int resultado=aux(ar1,a);
    int resu=aux(ar1,b);

    printf("%d\n%d\n",resultado,resu);
    return 0;
}