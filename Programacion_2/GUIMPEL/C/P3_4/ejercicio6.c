//? GESTIÓN DE LA MEMORIA.

//6 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <stdlib.h> 


int main() {
    int v[4] = { 2,4,5,7}, a, *p;  
    p = v+2;  //v[0]+2=v[2] , p apunta a "5"
    p--; //v[1] , p apunta a "4"
    a = *p + *(p+1) + *(v+1) + p[2];  // *p + (*p+1) == p[0]+p[1] == v[1]+v[2] == 4+5=9 . *(v+1)=v[1]=4 y p[2]=v[3]=7 , 9+4+7=20==a
    printf(" %d", a);  //20

    return 1;
}

    