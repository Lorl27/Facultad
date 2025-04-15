#include "longitud.h"
#include <stdio.h>

int string_len(char* str){
    
    if(str==NULL){
        return 0;
    }

    int contador=0;

    for(int x=0;str[x]!='\0';x++){
        contador++;
    }
    return contador;
}
