// Ejercicio 17. Definir una función esRectangulo que tome tres enteros y devuelva 1 si los
// números que se le pasan pueden ser los lados de un triángulo rectángulo, y 0 en caso contrario.
// Sugerencia: una manera sería verificar si el cuadrado del mayor es igual la suma de los 
// cuadrados de los otros dos. 
//Sin embargo existe otra manera utilizando solo una vez una función max3, 
//que devuelve el máximo entre tres enteros dados. Definir ambas funciones y probar
// esRectangulo con las entradas (3,5,4), (5,13,12) y (7,3,5).

#include <stdio.h>
#include <assert.h>
#include "ej16.h"

int esRectangulo_OP1(int a,int b,int c){
    int maximo=maximun_3(a,b,c);

     return (maximo == a) ? (a * a == b * b + c * c) :
           (maximo == b) ? (b * b == a * a + c * c) :
                           (c * c == b * b + a * a);
}

void test_esRectangulo_OP1(void){
    assert(esRectangulo_OP1(1,2,3)==0); //no es
    assert(esRectangulo_OP1(3,5,4)==1);
    assert(esRectangulo_OP1(5,13,12)==1); // sí es
    assert(esRectangulo_OP1(7,3,5)==0);
}

int esRectangulo_OP2(int a,int b,int c){
    return(a>b && a>c)?(a*a==b*b*+c*c):(b>c&&b>a)?(b*b==c*c+a*a):(c*c==b*b+a*a);
}

void test_esRectangulo_OP2(void){
    assert(esRectangulo_OP2(1,2,3)==0); //no es
    assert(esRectangulo_OP2(3,5,4)==1);
    assert(esRectangulo_OP2(5,13,12)==1); // sí es
    assert(esRectangulo_OP2(7,3,5)==0);
}

int main(void){
    //TEST:
    test_esRectangulo_OP1();
    test_esRectangulo_OP2();

    int a,b,c,resultado1=0,resultado2=0;
    printf("Ingresa los lados que quieres evaluar: \n");
    scanf("%d%d%d",&a,&b,&c);

    resultado1=esRectangulo_OP1(a,b,c);
    resultado2=esRectangulo_OP2(a,b,c);

    (resultado1 && resultado2)? printf("Tus lados forman un triangulo rectangulo!") : (printf("No lo forman..."));

    return 0;
}