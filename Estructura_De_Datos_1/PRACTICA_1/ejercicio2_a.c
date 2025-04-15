// a) int string len(char* str), que retorne la longitud de la cadena str, excluyendo el car´acter nulo
// (’\0’).
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

int main(){
    char array[]="domingo";
    char array2[]="";

    int r1,r2;

    r1=string_len(array);
    r2=string_len(array2);

    printf("La longitud de array es: %d y la de array2: %d \n",r1,r2);

    return 0;
}