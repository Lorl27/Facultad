// 1. Entrada/Salida
// Ejercicio 1. ¿Cuál es la salida del siguiente programa?
#include <stdio.h>

int main ()
{
int a, b, c, d=6, e;
a = b = 3;
c = a*b+d; //3*3+6=9+6=15
e = (c + 5) / 4-3; //20/4-3=5-2=2
e+=5; //2+5=7
printf("Los resultados son %d y %d ", c, e);
return 0;
}

//la salida será:  15 y 20