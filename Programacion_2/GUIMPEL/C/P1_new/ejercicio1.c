#include <stdio.h>

//? 1.ENTRADA/SALIDA

//Ejercicio 1: ¿Cuál es la salida del siguiente programa?

int main(){
    int a,b,c,d=6,e;

    a=b=3;
    c=a*b*d; //* 3*3*6=54
    e=(c+5)/(4-3); //* 59
    e+=5; //* 64

    printf("Los resultados son %d y %d", c,e);

    return 0;
}

//* La salida será:  54 y 64.