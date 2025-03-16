// Ejercicio 6. Escriba un programa que tenga un número secreto entre 0 y 500 el cuál estará
// fijo (use #def ine para esto). El usuario deberá, mediante el ingreso de números, adivinar dicho
// valor, en cada intento el programa debe responder el número es mayor o el número es menor,
// según corresponda. El usuario dispondrá como máximo de 15 intentos.

#include <stdio.h>
#include <assert.h>

#define NUM_SECRETO 20


void relacion_num(int num){
    (num>NUM_SECRETO)?(printf("El numero secreto es menor!")):(printf("El numero secreto es mayor!"));
}

int Adivinador(){
    int intentos=0;
    int number=0;
    do{
        printf("Ingrese el numero a adivinar:");
        scanf("%d",&number);
        
        if(number==NUM_SECRETO){printf("¡ADIVINASTE!\n");return 0;}

        relacion_num(number);

        intentos+=1;
        printf("Intento nro %d\n",intentos);

    }while(intentos<15);

    
    
    printf("NO LO HICISTE...El número secreto era %d.\n", NUM_SECRETO);return 1;
    
}


int main(){
    Adivinador();
    return 0;
}