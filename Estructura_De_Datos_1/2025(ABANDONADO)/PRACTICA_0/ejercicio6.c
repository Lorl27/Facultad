// 6. Implemente una funci ́on char *get new line(void) que ingrese una linea por teclado (hasta \n), y
// devuelva un puntero a la cadena ingresada

#include <stdio.h>
#include <stdlib.h>


char* get_new_line(void){

    char *linea = malloc(sizeof(char) * 100);  
    if (linea == NULL) {
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    printf("ingrese la linea: \n");
    fgets(linea, 100, stdin);

    return linea;
}


int main(){

    char *p=get_new_line();

    if(p!=NULL){

        for(int x=0;p[x]!='\0';x++){
            if(p[x]!='\n'){
            printf("Elemento nro %d del array: %c\n",x+1,p[x]);}
        }

        free(p);
    }

    return 0;
}