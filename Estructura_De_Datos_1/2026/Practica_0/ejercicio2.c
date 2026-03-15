#include <stdio.h>


void set_first(int arr[]){
    arr[0]=0;
}


int main(){
    int array[]={1,2,3};

    printf("array antes de modificarlo:\n");
    for (int x=0;x<3;x++){
        printf("array[%d]=%d\n",x,array[x]);
    }

    set_first(array);
    
    printf("array despu+es de modificarlo:\n");
    for (int x=0;x<3;x++){
        printf("array[%d]=%d\n",x,array[x]);
    }

    return 0;
}


/*

C siempre para los argumentos por  valor, sin embargo se modifcò el original porque lo que hace C con un arreglo es:
Array Decay , es decir convierte el array a puntero para ahorrar memoria.
Como la función set_first tiene la dirección real del array original, 
cuando hace arr[0] = 0; (que es equivalente a decir *arr = 0;), viaja a esa dirección exacta en la memoria RAM y modifica el valor original.

*/