//? GESTIÓN DE LA MEMORIA.

//1 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <stdlib.h> 


int main(){

    int* punt;  //crea un puntero de enteros
    int x=7;  
    int y = 5;
    punt=&x;  //le asigna al puntero, la direccion de la var x (x=7)
    *punt = 4; //ahora, x vale 4
    printf(" %d %d", x, y);  //4 y 5.

    }
