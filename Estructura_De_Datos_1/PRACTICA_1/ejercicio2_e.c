// int string subcadena(char* str1, char* str2), que retorne el  ́ındice de la primera ocurrencia
// de la cadena str2 en la cadena str1. En caso de no ocurrir nunca, retorna −1

#include <stdio.h>
#include <stdlib.h>
#include "longitud.h"

int string_subcadena(char* str1,  char* str2){
    int len1=string_len(str1);
    int len2=string_len(str2);

    for(int x=0;x<len1;x++){
        for(int y=0;y<len2;y++){
            if(str1[x]==str2[y]){
                return x; //encontrado
            }
        }
    }

    return -1; //no encontrado
}

int main(){
    char array[]="abc";
    char array2[]="abcd";
    char array3[]="msabcdddda";
    char array4[]="z";
    char array5[]="abc";

    int r1=0,r2=0,r3=0,r4=0,r5=0;

    r1=string_subcadena(array,array2);  //0
    r2=string_subcadena(array3,array2);  //2 
    r3=string_subcadena(array3,array4);  //-1 
    r4=string_subcadena(array4,array5); //-1 
    r5=string_subcadena(array,array5);  //0 

    printf("r1:%d,r2:%d;r3:%d,r4:%d,r5:%d",r1,r2,r3,r4,r5);

    return 0;
}