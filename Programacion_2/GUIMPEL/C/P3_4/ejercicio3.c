//? GESTIÓN DE LA MEMORIA.

//3 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <stdlib.h> 


int main(){

    int* punt , i;  //puntero - entero
    int x[]={1, 2, 3, 4, 5}; ///array de enteros
    punt = x;  // puntero con dir del array , es decir, dir del primer elemento x[0]=1
    *punt = 9; //x[0]=9

    for(i=0; i<5; i++){
        printf(" %d", x[i]);   //9-2-3-4-5.
    }

    }


    