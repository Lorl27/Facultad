// f) void string unir(char* arregloStrings[], int n, char* sep, char* res), que concatene
// las n cadenas del arreglo arregloStrings, separ ́andolas por la cadena sep y almacenando el resul-
// tado en res.
// Nota: Si res no tiene espacio suficiente para almacenar el resultado, el comportamiento queda
// indefinido.

#include <stdio.h>
#include <stdlib.h>
#include "longitud.h"

/** 
 * char *var[2];
 * c[]={"hola","mama","domingo" }. string_unir(c,2,"_",var)
 */

void string_unir(char *arregloStrings[], int n, char *sep, char *res){
    int index=0;

    for(int x=0;x<n;x++ ){ 
        char *string=arregloStrings[x]; 

        for(int y=0;string[y]!='\0';y++){
            res[index++]=string[y]; //copiamos cada carácter.
        }

        if(x < n-1){ //si no es el último: agregamos sep
            for(int k=0;sep[k]!='\0';k++){
                res[index++]=sep[k];
            }
        }

        res[index]='\0';
    }

    
}

int main(){
    char var[100];
    
    char *array[]={"hola","mama","domingo" };
    string_unir(array,3,"_jumanji:",var);

    printf("cadena unida: %s \n",var); //Resultado: hola_mama_domingo

    return 0;
}