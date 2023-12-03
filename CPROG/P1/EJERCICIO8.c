// Ejercicio 8. Escriba un programa que lea un valor positivo y haga la siguiente secuencia: si
// el número es par, debe dividirlo entre 2; si es impar, debe multiplicarlo por 3 y sumarle 1. La
// secuencia debe repetirse hasta que el valor sea 1, imprimiendo cada valor. También se deberá
// imprimir cuántas operaciones de estas fueron realizadas. Si el valor ingresado es menor que
// 1, imprima un mensaje que contenga la palabra Error. Un ejemplo de la salida del programa
// podría ser el siguiente:
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

int main(){
    int num,contador=0;
    printf("ingrese un numero positivo:\n");
    scanf("%i",&num);
    if(num<1) {printf("error"); return 1;}

    printf("Tu valor inicial es: %i\n",num);
    
    while(num!=1){
        if(num%2==0){
            num/=2;
            printf("El sigueinte valor es: %i\n",num); }
        else{
            num*=3;
            num+=1;
            printf("El sigueinte valor es: %i\n",num); 
        }
        contador+=1;
    }
    printf("VALOR FINAL 1 HALLADO.Nro de pasos: %i \n",contador);
    return 0;
}