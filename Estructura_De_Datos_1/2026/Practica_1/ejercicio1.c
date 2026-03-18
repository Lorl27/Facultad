#include <stdio.h>
#include <stdlib.h>

void bubble_sort(float arreglo[], int longitud)
{
    for (int iter = 0; iter < longitud - 1; iter++)
    {
        for (int i = 0; i < longitud - iter - 1; i++)
        {
            if (arreglo[i] > arreglo[i + 1])
            {
                float aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
            }
        }
    }
}

float calcular_promedio(float * arreglo, int longitud){
    float num_medio_1=arreglo[(longitud/2)-1];
    float num_medio_2=arreglo[(longitud/2)];
    return (num_medio_1+num_medio_2)/2.0;
}

float calcular_medio(float * arreglo, int longitud){
    return arreglo[longitud/2];
}

float mediana(float * arreglo, int longitud){
    float resultado;

    float *arreglo_copia = malloc(longitud * sizeof(float));
    if (arreglo_copia == NULL) return 0.0;

    for (int i = 0; i < longitud; i++) {
        arreglo_copia[i] = arreglo[i];
    }

    bubble_sort(arreglo_copia,longitud);
    resultado=  (longitud%2==0)? calcular_promedio(arreglo_copia,longitud): calcular_medio(arreglo_copia,longitud);

    free(arreglo_copia);

    return resultado;
}




int main(){
    float  arr1[]={-1.0,2.2,2.9,3.2,3.5};
    float  arr2[]={1.0,2.2,2.9,3.1};

    float resultado=mediana(arr1,5);
    float resultado2=mediana(arr2,4);

    printf("la mediana de arr1 es: %.2f y la de array2: %.2f",resultado,resultado2);
    return 0;
}