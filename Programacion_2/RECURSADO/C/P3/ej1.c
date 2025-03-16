// 1. Ejercicios Simples con Estructuras
// Ejercicio 1. ¿Cuál es la diferencia entre los siguientes tres programas?

#include <stdio.h>

//A:

struct point{
    double x;
    double y;
    };

int main(void){
    struct point test;
    test.x= .25;
    test.y=.75;

    printf("[%f%f]\n",test.x,test.y);
    
    return 0;
}

//Este código genera una struct que permite almanecar 2-uplas Double

//B:

typedef struct{
    double x;
    double y;
} Point;

int main(void){
    Point test;
    test.x=.25;
    test.y=.75;
    printf("[%f%f]\n",test.x,test.y);

    return 0;
}

//Este código hace lo mismo que A, solo que define a la estructura con un nombre, para así evitar ewcribir 'struct' al crear un nuevo objeto.

//C:

typedef struct {double x;
double y;} Point;

int main(void){
    Point test={.25,.75};
    printf("[%f%f]\n",test.x,test.y);

    return 0;
}

//Este codigo hace lo mismo que A y la define con Point (como B), la diferencia es que sus datos se pasan a la par.


