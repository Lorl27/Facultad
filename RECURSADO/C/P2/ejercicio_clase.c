//CREAR UNA DEFINICIÓN PROPIA DE strlen(STR)

#include <stdio.h>
#include <assert.h>
#include <string.h>

int calcular_longitud(char *string){
    int longitud=0;
    for(int x=0;string[x]!='\0';x++){
        longitud++;
    }
    return longitud;
}

void test_calcular_longitud(void){
    char string1[]={'h','o','l','a','\0'};
    char string2[]="Mucho gusto";
    assert(calcular_longitud(string1)==4);
    assert(calcular_longitud(string2)==11);
    assert(calcular_longitud("")==0);
}



int main(void){
    test_calcular_longitud(); //TEST

    char string[500];
    printf("Ingrese la palabra que desea calcular su longitud: ");
    scanf("%s",&string);
    int longitud=calcular_longitud(string);

    printf("Su longitud es: %d \n", longitud);
    printf("La cadena \"%s\" tiene longitud %d",string,strlen(string));
    return 0;
}