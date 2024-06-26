// Ejercicio 11. Escriba un programa que pida dos números y muestre todos los números que
// van desde el primero al segundo. Se debe controlar que los valores son correctos, es decir, que
// el primero es menor que el segundo.

#include <stdio.h>
#include <assert.h>

int CualEsMayor(int a,int b){
    return (a>b)? a:b;
}

void test_CualEsMayor(void){
    assert(CualEsMayor(5,4)==5);
    assert(CualEsMayor(5,5)==5);
    assert(CualEsMayor(4,25)==25);
}

void imprimir_numeros(int a,int b){
    int numero=a;
    while(numero<=b){ //a<b
        printf("El numero es: %d \n",numero);
        numero+=1;
    }
}

int main(){
    test_CualEsMayor(); //test
    
    int a,b;
    printf("Ingresa el valor del primero y segundo numero:\n");
    scanf("%d%d",&a,&b);

    if(CualEsMayor(a,b)==b){
        imprimir_numeros(a,b);
    }else{printf("ERROR. EL SEGUNDO ES MENOR QUE EL PRIMERO!");}
    
    

    return 0;
}