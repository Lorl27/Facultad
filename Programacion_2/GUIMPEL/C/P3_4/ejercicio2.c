//? GESTIÓN DE LA MEMORIA.

//2 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <stdlib.h> 


int main(){

    int* punt;
    int x=7;
    int y = 5;
    punt=&x;   //guarda la dir de x(x=7)
    x = 4;  //x vale 4 (y puntero tmb)
    punt=&y;  // puntero ahora guarda la direccion de y = 5
    printf(" %d %d", *punt , x); // 4 y 5.

    }
