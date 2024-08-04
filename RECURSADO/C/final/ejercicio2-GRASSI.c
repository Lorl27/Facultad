#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define TAM 400 //Definimos un tamaño máximo para los mensajes por telégrafo.

//Próposito de las funciones:
int buscar_letra(char array[],char letra);
int calcular_envio(char array[]);

/*  DISEÑO DE DATOS:

    longitud: int, indica el tamaño del array pasado por parámetro.

    Signatura:
    buscar_letra: char[] char -> int

    Próposito: Busca en la cadena parada por parámetro, alguna coincidencia de la letra pasada por paramétro.
    - En caso de encontrarla, retorna 1
    - En caso de que no este, retorna 0.

    EJEMPLOS:
        buscar_letra("amelia",'a')==1; //Está
        buscar_letra("amelia",'p')==0; //No está

*/

int buscar_letra(char array[], char letra){
    int longitud=strlen(array);

    for(int x=0;x<longitud;x++){
        if(array[x]==letra){
            return 1; //Se encontró la letra
        }
    }

    return 0; //No se encontró la letra

}

void test_buscar_letra(void){
    assert(buscar_letra("amelia",'a')==1); //Está
    assert(buscar_letra("amelia",'p')==0); //No está
}

/* DISEÑO DE DATOS:

    precio: int , es donde almacenaremos el precio total
    abc: char[] , una cadena con el alfabeto inglés
    digitos: char[], una cadena con todos los dígitos [0-9]
    carac_Especiales: char[], una candena con todos los cáracteres especiales (no letrás, no números)   

    Signatura:
    calcular_enviio: char[]->int

    Próposito: Calcular el coste total del envío de un mensaje según los precios establecidos por cada tipo de cáracter(letra,dígitos,cáracter especial).

    EJEMPLOS:
        calcular_envio("hola como estas?")==160; //letras=130 + carac_especiales=30 . precio=160
        calcular_envio("Manana, 2pm")==130; //letras=80 + digitos=20 + carac_especiales=30 . precio=130
*/



int calcular_envio(char array[]){
    int precio=0;

    char abc[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char digitos[]="0123456789";
    char carar_Especiales[]="!#$%&/()=?¡,.-_;[]{}";

    for(int x=0;array[x]!='\0';x++){
        if(buscar_letra(abc,array[x])){
            precio+=10;
        }
        if(buscar_letra(digitos,array[x])){
            precio+=20;
        }
        if(buscar_letra(carar_Especiales,array[x])){
            precio+=30;
        }
    }
    
    return precio;
}

void test_calcular_envio(void){
    assert(calcular_envio("hola como estas?")==160); //letras=130 + carac_especiales=30 . precio=160
    assert(calcular_envio("Manana, 2pm")==130); //letras=80 + digitos=20 + carac_especiales=30 . precio=130)
}



int main(void){

    //TESTS DE LAS FUNCIONES:
    test_buscar_letra();
    test_calcular_envio();

    char mensaje[TAM];
    int costo=0;

    printf("Ingrese el mensaje por telégrafo: \n");
    
    fgets(mensaje,sizeof(mensaje),stdin); //Utilizamos fgets para poder leer cadenas largas
    mensaje[strcspn(mensaje,"\n")]='\0'; //Eliminamos el salto de línea

    costo=calcular_envio(mensaje);

    if(costo==0){
        printf("Usted no ha enviado ningún mensaje, o éste estaba vacío.");
    }
    else{
    printf("El coste del envío del mensaje \"%s\" es de: $%d \n",mensaje,costo);
    }


    return 0;
}