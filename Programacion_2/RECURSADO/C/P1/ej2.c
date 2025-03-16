// Ejercicio 2. ¿Cuál es la salida del siguiente programa?

#include <stdio.h>
int main ()
{
int a, b, c, d=6, e;
a = 3;
b = a - d / 3; //3-2=1
a *=b; //a=3
c = a + d / a - 3 / a * b; //3+2-1=4
e = c + 8 / 4-b; //4+2-1=5
e+=5;//10
printf("Los resultados son %d y %d ", c, e); //4 y 10
return 0;
}