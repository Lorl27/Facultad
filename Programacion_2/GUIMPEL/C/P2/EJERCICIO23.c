// Ejercicio 23. Escriba una función que reciba dos cadenas de caracteres y determine si una
// está contenida dentro de la otra

#include <stdio.h>
#include <string.h>

int aux(char cad[],char cad2[]){
    int largo1=strlen(cad);
    int largo2=strlen(cad2);
    
    for (int x=0; x<=largo2-largo1; x++) { //sup cad2 la + larga
        int m;

        for (m=0; m<largo1; m++) {
            // printf("%c-%c\n",cad[m],cad2[x+m]);
            if (cad[m]!=cad2[x + m]) {
                break;
            }
        }

        if (m == largo1) {
            return 0; // La primera cadena está completamente contenida en la segunda
        }
    }

    return 1; // No está contenida
}



int main(){
    char am[]="am";
    char amelia[]="amelia";

    int resultado=aux(am,amelia);
    int resul=aux(amelia,am);

    printf("%d\n%d\n", resultado,resul);
}
