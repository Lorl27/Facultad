// Ejercicio 12: Escriba un programa que dado un número ingresado determine si el mismo es primo o no.

//? nro/1 && nr0

#include <stdio.h>

int primo(int num){
    if(num<2){
        return 1; //NO PRIMO
    }

    if(num==2){
        return 0; // 2 es el único número par primo
    }
    if(num%2==0){
        return 1; 
    }

    for(int i=3; i*i<=num; i+=2){
        if(num%i==0){
            return 1; // Si es divisible por otro número, no es primo
        }
    }
    return 0; // primo

}

int main(){
    int number;
    printf("Ingrese el nro: \n");
    scanf("%d",&number);

    if(!primo(number)){
        printf("PRIMO!");
    }
    else{printf("No primo.");}

    return 0;
}