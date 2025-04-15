// c) int string concat(char* str1, char* str2, int max), que concatene no m ́as de max carac-
// teres de la cadena str2 al final de la cadena str1. El car ́acter inicial de str2 debe sobrescribir
// el car ́acter nulo de str1. La cadena resultante debe terminar con un car ́acter nulo. Retorna el
// n ́umero de caracteres copiados.
// Nota: Si str1 no tiene espacio suficiente para almacenar el resultado, el comportamiento queda
// indefinido

#include <stdio.h>
#include <stdlib.h>
#include "longitud.h"

int string_concat2(char *str1, char *str2, int max){
    if (str1 == NULL || str2 == NULL || max <= 0) return 0;

    int len1 = string_len(str1);
    int i;

    for (i = 0; i < max && str2[i] != '\0'; i++) {
        str1[len1 + i] = str2[i];
    }

    str1[len1 + i] = '\0'; 
    return i; // Cantidad de caracteres copiados
}


int string_concat2(char *str1, char *str2, int max){
    if(str1==NULL||str2==NULL ||max<=0){
        return 0;
    }

    int len1=string_len(str1);
    char *aux=malloc(sizeof(char)*(max+1));
    if(aux==NULL){
        printf("fallo en asignar memoria");
        return 0;
    }
    
    int x;
    for(x=0;x<max && str2[x]!='\0' ;x++){  //solo copiamos la cant. de caracteres que queremos
        aux[x]=str2[x];
    }

    aux[x]='\0';

    //ahora debemos incorporar aux al final de str1.


    for(int i=0;aux[i]!='\0';i++){
        str1[len1+i]=aux[i];
    }

    str1[len1+x]='\0';

    free(aux);  //ya no lo necesitamos.

    return x; //cant. caracteres que copiamos

}

int main(){
    char array[100]="domingo";
    char array2[]="Concatenaje";

    string_concat(array,array2,3);
    printf("Al concatenar array2 con array1, max=3: %s \n",array);

    string_concat(array,array2,10);
    printf("Al concatenar array2 con array1, max=10: %s \n",array);

    return 0;
}