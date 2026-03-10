// b) void string reverse(char* str), que invierta la cadena str

#include <stdio.h>
#include <stdlib.h>
#include "longitud.h"

// idea: str=domingo -> copia=ognimod domingo[0]=copia[ultimo] , domingo[ultimo]=copia[0]
void string_reverse(char *str){
    int longitud =string_len(str);
    char *copia=malloc(sizeof(char)*(longitud+1)); //+1 porque string_leng no tiene en cuenta el '\0'

    for(int x=0;x<longitud;x++){ //Copiamos la cadena 
        copia[x]=str[longitud-1-x]; //longitud-1 = último valor, x=0 --> copia[0]=str[ultimo]
    }

    copia[longitud]='\0';

    for(int x=0;x<=longitud;x++){ //Copiamos la cadena 
        str[x]=copia[x];
    }
    
    free(copia);
    
}

int main(){
    char array[]="domingo";
    char array2[]="";

    string_reverse(array2);
    string_reverse(array);
    printf("La inversa de de array es: %s y la de array2: %s \n",array,array2);

    return 0;
}