//? GESTIÓN DE LA MEMORIA.

//7 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <stdlib.h> 

void suma_dos(int* x, int* y, int z){  //funcion que agarra 2 punteros y un entero - 
    *x = *x + 2; //x[0]+=2
    *y = *y + 5; //y[0]+=5
    z = z + 4;
}
int main() {
    int x, y, z;
    x = 3;
    y = 10;
    z = 15;
    suma_dos (&x, &y, z);  //x+2 , y+5 , z queda normal 
    printf(" %d %d %d", x, y, z);  //5,15,15
    return 1;
}