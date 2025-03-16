// Ejercicio 11: Escriba un programa que pida dos números y muestre todos los números que van desde el primero al segundo.
// Se debe controlar que los valores son correctos, es decir, que el primero es menor que el segundo.


#include <stdio.h>

int control(int a, int b){
    return a<b;
}

int lista_nums(int a, int b){
    int contador=a;
    while(contador <=b){
        printf("%d\n",contador);
        contador++;
    }
}

int main(){
    int nro1;
    int nro2;
    
    printf("Elige 2 nros: (a<b) \n");
    scanf("%d%d",&nro1,&nro2);

    if(!control(nro1,nro2)){
        printf("%d es mayor que %d",nro1,nro2);
        return 1;
    }

    lista_nums(nro1,nro2);

    return 0;

    
}