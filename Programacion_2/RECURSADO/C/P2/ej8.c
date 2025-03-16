// Ejercicio 8. Leer un valor positivo, y hacer la siguiente secuencia: si el número es par, dividirlo entre 2;
// si es impar, multiplicarlo por 3 y sumarle 1. Repetir lo anterior hasta que el valor
// sea 1, imprimiendo cada valor, también se deberá imprimir cuantas operaciones de estas son
// hechas en cambio, si el valor ingresado es menor que 1, imprimir un mensaje que contenga la
// palabra Error. Un ejemplo de la salida del programa podría ser el siguiente:
// El valor inicial es 9
// El siguiente valor es 28
// El siguiente valor es 14
// El siguiente valor es 7
// El siguiente valor es 22
// El siguiente valor es 11
// El siguiente valor es 34
// El siguiente valor es 17
// El siguiente valor es 52
// El siguiente valor es 26
// El siguiente valor es 13
// El siguiente valor es 40
// El siguiente valor es 20
// El siguiente valor es 10
// El siguiente valor es 5
// El siguiente valor es 16
// El siguiente valor es 8
// El siguiente valor es 4
// El siguiente valor es 2
// Valor final 1, número de pasos 19.


#include <stdio.h>

void condicion(int num){
    int pasos=0;
    printf("El valor inicial es %d\n", num);
    while(num!=1){
        if((num%2)==0){
            num/=2;
            
        }

        else{
            num*=3;
            num+=1;
        }
        
        pasos++;

        if (num != 1) {
            printf("El siguiente valor es %d\n", num);
        }

    }

    printf("Valor final 1. Nro de pasos: %d",pasos);
}

int main(void){
    int numero;
    printf("Ingrese  un numero: ");
    scanf("%d",&numero);

    if(numero<1){printf("Error."); return 1;}
    
    condicion(numero);

    return 0;
}