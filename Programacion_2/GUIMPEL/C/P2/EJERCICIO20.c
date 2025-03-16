// Ejercicio 20. Escriba un programa que lea por teclado una cadena de caracteres y la imprima
// por pantalla al revés.

#include <stdio.h>
#include <string.h>

int main(){
    char arr[100];
    printf("ingrese su cadena de caracteres:");
    fgets(arr,sizeof(arr),stdin); //w scanf:scanf("%99s", cadena); limit con espacios/tab+u need a lote 

    printf("La cadena que ingresaste es: %s", arr);

    printf("La cadena al revés es: ");
    
    int largo=strlen(arr);
    
    for(int x=largo-1; x>=0; x--){
        printf("%c", arr[x]);
    }

    return 0;
}