// Ejercicio 12. Escriba un programa que lea un arreglo a de 10 enteros y un entero n y que
// imprima el índice del arreglo a donde se encuentra n si está presente en el arreglo y, -1 en caso
// contrario.


#include <stdio.h>

void completar_arreglo(int *arreglo_a){
    for(int x=0;x<10;x++){
        printf("Ingresa el nro correspondiente a la pos %d: ",x);
        scanf("%d",&arreglo_a[x]);
    }
}

int buscar_indice(int *arreglo, int index,int tam){
    for(int x=0;x<tam-1;x++){
        if(arreglo[x]==index){
            return x;
        }
    }
    return -1;
}

int main(void){
    int array[10],entero;

    completar_arreglo(array);

    printf("Ahora, ingrese un entero: ");
    scanf("%d",&entero);

    int tam=sizeof(array)/sizeof(array[0]);

    int resultado=buscar_indice(array,entero,tam);

    if(resultado!=-1){
        printf("Se encontro en la posicion nro: %d \n",resultado);
    }else{printf("No se encontro...");}

    return 0;
}