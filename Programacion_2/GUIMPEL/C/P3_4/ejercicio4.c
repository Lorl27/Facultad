//? GESTIÓN DE LA MEMORIA.

//4 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <stdlib.h> 


int main(){

    int* punt , i;
    int x[]={1, 2, 3, 4, 5}; 
    punt = x;
    *(punt +2) = 9; //  puntero[2]==9 --> x={1,2,9,4,5}
    *(x+3) = 7;  //x[3]==7 --> x={1,2,9,7,5}
    punt [1]=11;  // x={1,11,9,7,5}
    for(i=0; i<5; i++){
        printf(" %d", *(punt+i));  //1-11-9-7-5
    }

    }


    