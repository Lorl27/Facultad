// 8. Implemente las siguientes funciones que reciben como argumento punteros a funci ́on:

// a) int apply(int (*)(int), int) que toma un puntero a funci ́on, y un entero, y aplica la funci ́on al
// entero y retorna el valor dado.

// b) void apply in(int (*)(int), int*) que toma un puntero a funci ́on, un puntero a un entero, y
// reemplaza el entero apuntado por el valor de ejecutar la funci ́on apuntada sobre el valor apuntado.

// c) void recorre(VisitorFunc, int[], int) que toma un puntero a una funci ́on, un arreglo de enteros,
// y su longitud, y aplica la funci ́on a cada elemento del arreglo. VisitorFunc est ́a definido por
// typedef void (*VisitorFunc)(int).

// d) Pruebe las funciones anteriores pas ́andoles como par ́ametro las siguientes funciones:
    // i. Para a y b:
        // int sucesor (int n) {
        // return n+1;
        // }
    // ii. Para c:
        // void imprimir (int n) {
        // printf("%d \n", n);
        // }

//---------------------------------------

#include <stdio.h>

//f. a puntero , int --> int
int apply( int (* fptr)(int ) , int b){ //aplica fptr a un entero y devuelve el resultado 
    return fptr(b);
}

//f. a puntero , puntero --> void.
void apply_in( int (* fptr_1)(int), int* puntero){ //aplica fptr a un puntero
    *puntero= fptr_1(*puntero);
}

typedef void (*VisitorFunc)(int);

// f. a puntero (int) , array de enteros, int --> void.
void recorre(VisitorFunc funcion, int array[], int longitud){  //aplica un fptr a cada elemento de un array
    for(int x=0;x<longitud;x++){
        funcion(array[x]);
    }
}

//------------------------

//A Y B:

int sucesor(int n){
    return n+1;
}

//C:
void imprimir(int n){
    printf("%d \n",n);
}

//----------------

int main(){

    int numero=5,resultado_a;

    resultado_a=apply(sucesor,numero);  
    printf("El resultado de A es: %d -> %d\n", numero, resultado_a);
    
    ////////////////
    int *puntero = &numero;

    apply_in(sucesor,puntero);
    printf("Ahora, puntero->numero es: %d\n",*puntero);

    ////////////
    int array[]={1,2,3};

    printf("Elementos del array:\n");
    recorre(imprimir,array,3);

    return 0;
}