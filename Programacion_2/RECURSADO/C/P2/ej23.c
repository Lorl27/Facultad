// Ejercicio 23. Escriba una función que reciba dos cadenas de caracteres y determine si una
// está contenida en la otra.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

/*DISEÑO DE DATOS: 
Calcularemos si la cadena1 está contenida en la cadena2
Es decir, cadena1<=cadena2! */

//forma 1:

// int contencion(char cadena1[],char cadena2[]){
//     int len1 = strlen(cadena1);
//     int len2 = strlen(cadena2);

//     if(len1>len2){return 1;} //NO contenida.

//     int x=0;
//     while(x<=len2-len1){
//         int y=0;
//         while(y<len1 && cadena2[x+y]==cadena1[y]){
//             y++;
//         }
//         if(y==len1){ return 0;} //Contenida! (llego al final)

//         x++; //en caso de no encontrar
//     }
    
//     return 1; //no lo esta 
// }

//forma 2:

int contencion(char cadena1[], char cadena2[]) {
    int len1 = strlen(cadena1);
    int len2 = strlen(cadena2);
    
    for (int x=0; x <= len2 - len1; x++) {
        int coincide = 1; // Suponemos que coincide al inicio

        for (int y = 0; y < len1; y++) {
            if (cadena2[x+y]!= cadena1[y]) {
                coincide = 0; // NO Coincide
            }
        }

        if (coincide && x + len1 <= len2) {
            return 0; // Si encontramos una coincidencia completa, retornamos 0
        }
    }
    return 1; // Si no encontramos ninguna coincidencia, retornamos 1
}

void test_contencion(void){
    assert(contencion("ameli","amelia")==0);
    assert(contencion("ameli","jennifer")==1);
    assert(contencion("hola", "que hola")== 0);
    assert(contencion("casa", "micasa")== 0);
}

int main(void){
    test_contencion(); //TEST

    char cadena_origen[300];
    char cadena_destino[300];

    printf("Ingrese la cadena a la cual evaluar su contencion: ");
    fgets(cadena_origen,sizeof(cadena_origen),stdin);
    cadena_origen[strcspn(cadena_origen,"\n")]='\0'; //sacar nl.
    printf("Ingrese la cadena a la cual quiere saber si está en \"%s\" ",cadena_origen);
    fgets(cadena_destino,sizeof(cadena_destino),stdin);
    cadena_destino[strcspn(cadena_destino,"\n")]='\0'; //sacar nl.

    int resultado=contencion(cadena_destino,cadena_origen);

    if(resultado){printf("No está contenida.");}
    else{printf("Si que lo está!");}

    return 0;
}