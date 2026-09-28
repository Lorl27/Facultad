// 17) Implemente una funcion en lenguaje C que tome tres parametros
//  a, b y c y que rote
// los valores de las variables de manera que al finalizar la funci´on 
// el valor de a se encuentre en b, el valor de b en c y el de c en a.
//  Evitar utilizar variables auxiliares.
// Ayuda: Tener en cuenta las propiedades del operador XOR. 
// Se puede pensar primero en intercambiar dos variables:
// x = x^y;
// y = x^y; pero ahora x = x^y, entonces y = x^y^y = x
// x = x^y; x = x^y^x = y
// Luego se puede extender a tres variables.
#include <stdio.h>
#include <stdlib.h>

void rotacion(long * a, long * b, long * c){ // a<->b y luego a=b entonces a<->c
    *a=*a^*b;
    *b=*a^*b; // a^b^b=a^0=a;
    *a=*a^*b; // a^a^b=0^b=b;

    *a=*c^*a; //=c^b;
    *c=*c^*a; //c^c^a=0^a=a;
    *a=*c^*a; //c^a^a=c^0=c;
}

int main(void) {
    long x = 10; // Originalmente a
    long y = 20; // Originalmente b
    long z = 30; // Originalmente c

    printf("Antes de rotar: x=%ld, y=%ld, z=%ld\n", x, y, z);

    rotacion(&x, &y, &z);

    // Resultado esperado: x=30 (c), y=10 (a), z=20 (b)
    printf("Despues de rotar: x=%ld, y=%ld, z=%ld\n", x, y, z);

    return 0;
}