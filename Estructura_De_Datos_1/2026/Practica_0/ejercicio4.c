#include <stdio.h>
#include <stdlib.h>

void imprimir_arreglo(int *arr, int tamano, char *nombre) {
    printf("%s: ", nombre);
    for (int i = 0; i < tamano; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int* var1, int * var2,int max_long){

    for(int x=0;x<max_long;x++){
        int cambio=var1[x];
        var1[x]=var2[x];
        var2[x]=cambio;
    }

}


void swap_simple(int  * int1, int * int2){
    int cambio=*int1;
    *int1=*int2;
    *int2=cambio;
}


int main(){

    int tam=10;
    int * arregloA=malloc(sizeof(int)*tam);
    int * arregloB=malloc(sizeof(int)*tam);

    for (int i = 0; i < tam; i++) {
        arregloA[i] = i + 1;       
        arregloB[i] = (i + 1) * 10;
    }

    printf("--- ANTES DEL SWAP ---\n");
    imprimir_arreglo(arregloA, tam, "Arreglo A");
    imprimir_arreglo(arregloB, tam, "Arreglo B");


    swap(arregloA,arregloB,tam);

    printf("\n--- DESPUES DEL SWAP ---\n");
    imprimir_arreglo(arregloA, tam, "Arreglo A");
    imprimir_arreglo(arregloB, tam, "Arreglo B");

    free(arregloA);
    free(arregloB);


    printf("Forma simple:\n");
    int a = 10;
    int b = 99;

    printf("Antes del swap: a = %d, b = %d\n", a, b);

    swap_simple(&a, &b);

    printf("Despues del swap: a = %d, b = %d\n", a, b);

    return 0;
}