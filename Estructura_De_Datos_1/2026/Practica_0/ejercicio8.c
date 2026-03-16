#include <stdio.h>
#include <stdlib.h>

typedef void (*VisitorFunc)(int);

int apply(int (* funcion)(int) , int entero){
    return funcion(entero);
}

void apply_in(int (* funcion)(int), int * entero){
    *entero=funcion(*entero);
}

void recorre( VisitorFunc funcion,int arreglo[], int arreglo_long){
    for(int x=0;x<arreglo_long;x++){
        funcion(arreglo[x]);
    }
}

//
int sucesor (int n) {
    return n+1;
}

void imprimir (int n) {
    printf("%d \n", n);
}
//

int main(){
    int TAM=10;
    int entero=5;
    int array[]={1,2,3,4,5,6,7,8,9,10};

    printf("--- Probando apply con sucesor ---\n");
    printf("Original: %d\n", entero);
    printf("Resultado de apply: %d\n\n", apply(sucesor, entero));
    
    printf("--- Probando apply_in con sucesor ---\n");
    printf("Original: %d\n", entero);
    apply_in(sucesor, &entero);
    printf("Resultado guardado in-place: %d\n\n", entero);
    
    printf("\nProbando la funciòn reccore con imprimir:\n");
    recorre(imprimir,array,TAM);
    return 0;

    
}