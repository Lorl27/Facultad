//? GESTIÓN DE LA MEMORIA.

//5 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <stdlib.h> 


int main(){

    int *punt ,i;
    int x[5]={1 ,2 ,3 ,4 ,5};
    punt=&x[0]+3;   //apunta a x[3]
    *(punt -2) =9;  //comenzamos en x[3] 3-2=1 , x[1]=9 , x={1,9,3,4,5}  //! aca no cambiamos el puntero de lugar, solo modificamos el valor en esa dirrecion
    punt --; //retrocedemos 1 elemento  (estamos todavia en x[3],ahora estamos en x[2]) //!aca si lo cambiamos de lugar
    *(punt)=7 ; //x[2]=7 -->x={1,9,7,4,5}
    punt [1]=11 ; //como estamos en x[2]  , punt[1]==(*punt+1)==x[3] x={1,9,7,11,5}
    punt=x; // apuntamos de nuevo a x[0] para poder imprimir bien el array.
    for(i=0;i<5;i++){
        printf(" %d,",punt[i]);} //1-9-7-11-5

    }


    