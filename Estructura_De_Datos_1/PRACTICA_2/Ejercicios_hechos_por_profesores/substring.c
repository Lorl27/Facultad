#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int string_subcadena_feo (char chico[], char grande[]){
    int i = 0;
    int j = 0;
    int inicio = -1;
    while (inicio == -1 && grande[i] != '\0' && chico[j] != '\0') {
        if (grande[i] == chico[0]){
            inicio = i;
            while (grande[i] == chico[j] && chico[j] != '\0' && grande[i] != '\0'){
                i++;
                j++;
            }
            if (chico[j] != '\0'){
                j = 0;
                i = inicio + 1;
                inicio = -1;
            }
        }
        else {
            i++;
        }
    }
    return inicio;
} 

int string_prefijo (char chico[], char grande[]){
    int i;
    for (i=0; grande[i] == chico[i] && chico[i] != '\0'; i++);

    if (chico[i] == '\0')
        return 1;
    return 0;
}

int string_subcadena_ok (char chico[], char grande[]){
    int inicio = -1;
    for (int i=0; grande[i] != '\0' && inicio == -1; i++){
        if(string_prefijo(chico, grande+i))
            inicio = i;
    }
    return inicio;
}


int main() {
    char grande[] = "batatas";
    char chico[] = "atas";

    printf("inicio subcadena: %d\n", string_subcadena_ok(chico, grande));
    return 0;
}