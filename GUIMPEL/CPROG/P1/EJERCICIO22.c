// Ejercicio 22. Escriba una función que reciba una cadena de caracteres y determine si es un
// pangrama, es decir, si para escribir la línea se utilizaron todos los caracteres del alfabeto


#include <stdio.h>
#include <string.h>
#include <ctype.h>

int aux(char cadena[]){
    char alfabeto[27]="abcdefghijklmnopqrstuvwxyz"; //26 ing y +1  fin
    int bandera=1;
    
    for(int x=0;alfabeto[x]!='\0';x++){
        char letra=tolower(alfabeto[x]); //nos aseguramos de que sea todo minus

        int found=0;
        
        for(int m=0;cadena[m]!='\0';m++){
        
            if(cadena[m]==letra){
                found = 1; // La letra del alfabeto se encuentra en la cadena
                break;
            }
        }

        if(found==0){
        bandera=0; //no pangrama
        break;}
    }

    return bandera; //1=pangrama y 0=no pangrama

}

int main(){
    char e[]="El veloz murcielago hindu comia feliz cardillo y kiwi. la ciguena tocaba el saxofon detras del palenque de paja";
    char m[]="hola";

    if(aux(e)){
        printf("La cadena 'e' es un pangrama.\n");
    } else {
        printf("La cadena 'e' no es un pangrama.\n");
    }

    if(aux(m)){
        printf("La cadena 'm'  es un pangrama.\n");
    } else {
        printf("La cadena 'm' no es un pangrama.\n");
    }

return 0;
}


//FORMA OPTIMIZADA:
/*
int letras[26] = {0}; // Inicializa un arreglo para contar las letras

    for(int i = 0; cadena[i] != '\0'; i++){
        char c = tolower(cadena[i]); // Convierte el carácter a minúscula

        if (c >= 'a' && c <= 'z') {
            int index = c - 'a'; // Obtiene el índice de la letra en el arreglo
            letras[index] = 1; // Marca la letra como encontrada
        }
    }

    for (int i = 0; i < 26; i++) {
        if (letras[i] == 0) {
            return 0; // No es un pangrama
        }
    }

    return 1; // Es un pangrama
}
*/

