// Ejercicio 16. Tres números positivos pueden ser la medida de los lados de un triángulo si y
// sólo si el mayor de ellos es menor que la suma de los otros dos. Escribir y probar una función
// ladosTriangulo que devuelva 1 si los tres números que se le pasan verifican esta condición, y
// 0 en caso contrario.

#include <stdio.h>
#include <assert.h>
#include "ej15.h"
#include "ej16.h"

int maximun_3(int a,int b,int c){
    return maximum(maximum(a,b),c);
}

void test_maximum_3(void){
    assert(maximun_3(6,7,5)==7);
    assert(maximun_3(60,7,5)==60);
    assert(maximun_3(6,7,50)==50);
}


int ladosTriangulo(int a,int b,int c){
    int max=maximun_3(a,b,c);

    if(max==a){return a<b+c;}
    else if(max==b){return b<a+c;}
    else{return c<a+b;}
}

void test_ladosTriangulo(void){
    assert(ladosTriangulo(5,6,7)==1); //si
    assert(ladosTriangulo(5,5,10)==0); //no
    assert(ladosTriangulo(4,6,7)==1); //si
}

/*int main(void){
    //TESTS:

    test_maximum_3();
    test_ladosTriangulo();

    int l1,l2,l3,resultado=0;

    printf("Ingrese los lados de un triangulo: \n");
    scanf("%d%d%d",&l1,&l2,&l3);

    resultado=ladosTriangulo(l1,l2,l3);

    if(resultado){printf("Son la medida de un triángulo!");}
    else{printf("NO lo son...");}

    return 0;
}*/

//NOTE: Para usar en el ej '17.c' , comentar MAIN.