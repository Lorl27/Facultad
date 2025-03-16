//HACER LA DEFINICION PROPIA DE strncpy(s1,s2,n) : copia n caracteres de s2 en s1!

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void copiar_n_strings(char s1[],char s2[], int n){
    for(int x=0; s2[x]!='\0' && x<n;x++){
        s1[x]=s2[x];
        s1[x+1]='\0';
    }
}

int main(void){
    char cadena_copy[100];
    char cadena_destino[100];
    int max_carac;

    printf("Ingrese la cadena que desea copiar: ");
    fgets(cadena_copy,sizeof(cadena_copy),stdin);

    printf("Ingrese el nro MAX de caracteres a copiar de \"%s\": ", cadena_copy);
    scanf("%d",&max_carac);

    copiar_n_strings(cadena_destino,cadena_copy,max_carac);


    printf("La cadena se copio exitosamente, resultado: %s \n",cadena_destino);

    strncpy(cadena_destino,"",max_carac); //clean data
    strncpy(cadena_destino,cadena_copy,max_carac);

    printf("La cadena se copio exitosamente, resultado: %s \n",cadena_destino);

    return 0;
}