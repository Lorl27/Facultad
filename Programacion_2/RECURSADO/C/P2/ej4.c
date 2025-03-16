// Ejercicio 4. Una terna de números naturales (a, b, c) es una terna pitagórica si a
// 2 + b
// 2 = c
// 2
// .
// Escriba un programa que imprima todas las ternas pitagóricas con a ≤ 20 y b ≤ 30.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define TOPERAND 90

int terna_pitagorica(int a,int b,int c){
    return (a*a+b*b==c*c);
}

void test_terna_pitagorica(void){
    assert(terna_pitagorica(3,4,5)==1); //T
    assert(terna_pitagorica(48,55,73)==1); //T
    assert(terna_pitagorica(3,2,5)==0); //F
}

int main(void) {
    test_terna_pitagorica(); // TEST

    srand(time(NULL)); // Inicialización de la semilla para números aleatorios

    for (int x = 1; x <= 20; x++) {
        for (int y = 1; y <= 30; y++) {
            int c = rand() % TOPERAND + 1; // Evitar c=0
            if (terna_pitagorica(x, y, c)) {
                printf("Terna pitagórica encontrada: (%d, %d, %d)\n", x, y, c);
            } /*else {
                printf("(%d, %d, %d) no es una terna pitagórica.\n", x, y, c);
            }*/
        }
    }
    return 0;
}