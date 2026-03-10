//? Pr´actica 1 - Arreglos

// 1. La mediana de un arreglo ordenado de n n´umeros se define como el elemento del medio cuando n es
// impar y como el promedio de los dos elementos del medio cuando n es par. Por ejemplo,
// mediana([-1.0, 2.2, 2.9, 3.1, 3.5]) = 2.9
// mediana([-1.0, 2.2, 2.9, 3.1]) = 2.55
// Escriba una funci´on que reciba un arreglo, no necesariamente ordenado, de n´umeros y calcule su mediana:
// float mediana(float *arreglo, int longitud);

// Puede utilizar la siguiente rutina para ordenar un arreglo de menor a mayor

#include <stdio.h>
#include <stdlib.h>

void bubble_sort(float arreglo[], int longitud) {

    for (int iter = 0 ; iter < longitud - 1 ; iter++) {
        for (int i = 0 ; i < longitud - iter - 1; i++) {

        if (arreglo[i] > arreglo[i + 1]) {
            float aux = arreglo[i];
            arreglo[i] = arreglo[i + 1];
            arreglo[i + 1] = aux;
        }
    }
    }
}
// Nota: La funci´on mediana no debe modificar el arreglo original

/**
 *  n par-> n/2 -> promedio entre 2 nums : (n-1 + n ) / 2
 * n impar -> n+1/2  -> n/2
 */

float mediana(float *arreglo, int longitud){

    float *ar_ord=malloc(sizeof(float)*longitud);
    float resultado=0;

    for(int x=0;x<longitud;x++){
        ar_ord[x]=arreglo[x]; ///lo copiamos
    }
    bubble_sort(ar_ord,longitud);

    if(longitud%2==0){  //par
        int medio=longitud/2;
        resultado=(ar_ord[medio-1]+ar_ord[medio])/2.0;
    }
    else{
        resultado=ar_ord[longitud/2];
    }
    
    free(ar_ord);
    return resultado;
}

int main(){
    float array1[]={-1.0, 2.2, 2.9, 3.1, 3.5};
    float array2[]={-1.0, 2.2, 2.9, 3.1};

    float r1,r2;

    r1=mediana(array1,5);
    r2=mediana(array2,4);

    printf("La mediana de array1 es %2.f y la de array2 es %.2f \n",r1,r2);

    return 0;
}