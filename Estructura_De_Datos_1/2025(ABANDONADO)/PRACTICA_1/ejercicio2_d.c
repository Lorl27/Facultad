// d) int string compare(char* str1, char* str2), que compare en orden lexicogr ́afico [alfabetico] las cadenas
// str1 y str2, y retorne retorne -1 si la primera es menor que la segunda, 0 si son iguales, y 1 si es
// mayor.

#include <stdio.h>
#include <stdlib.h>
#include "longitud.h"

int string_compare(char* str1,char* str2){
    
    if(str1==NULL || str2==NULL){
        return -2;
    }

    int len1=string_len(str1);
    int len2=string_len(str2);

    int max_long;
    len1>len2?(max_long=len1):(max_long=len2);

    for(int x=0;x<max_long;x++){
        if(str1[x]>str2[x]){
            return 1;
        }

        if(str1[x]<str2[x]){
            return -1;
        }

        
    }

    return 0;
}

int main(){
    char array[]="abc";
    char array2[]="abcd";
    char array3[]="abcdddda";
    char array4[]="z";
    char array5[]="abc";

    int r1=0,r2=0,r3=0,r4=0,r5=0;

    r1=string_compare(array,array2);  //-1 (bien)
    r2=string_compare(array2,array3);  //1 (bien)
    r3=string_compare(array3,array4);  //-1 (bien)
    r4=string_compare(array4,array5); //1 (bien)
    r5=string_compare(array,array5);  //0 (bien)

    printf("r1:%d,r2:%d;r3:%d,r4:%d,r5:%d",r1,r2,r3,r4,r5);

    return 0;
}