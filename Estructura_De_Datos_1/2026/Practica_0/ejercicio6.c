#include <stdio.h>
#include <stdlib.h>

char * get_new_line(void){
    char *p = malloc(sizeof(char)*100);
    if(p==NULL) return NULL;
    printf("Ingrese linea aqui:\n");
    if (fgets(p, 100, stdin) == NULL) {
        free(p);
        return NULL;
    }
    return p;
}


int main(){
    char *cadena;
    cadena=get_new_line();
    if(cadena==NULL) return 1;
    printf("cadena generada: %s",cadena);
    free(cadena);
    return 0;

}