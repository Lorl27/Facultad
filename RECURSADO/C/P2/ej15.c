// Ejercicio 15. Escriba una función sumaArr que tome un arreglo de enteros junto con la longitud del mismo
// y devuelva la suma de sus elementos.

#include <stdio.h>
#include <assert.h>

int pedir_tamanio(){
    int tam;
    printf("Ingrese el tamaño de su array: ");
    scanf("%d",&tam);
    return tam;
}

void completar_Arreglo(int *array,int size){
    for(int x=0;x<size;x++){
        printf("Ingrese el entero en la pos nro %d: ",x+1);
        scanf("%d",&array[x]);
    }
}


int sumaArr(int *array,int size){
    int suma=0;
    for(int x=0;x<size;x++){
        suma+=array[x];
    }
    return suma;
}

void test_sumaArr(void){
    int array1[] = {1, 2, 3, 4};
    int array2[] = {10, 2, 3, 4,9};
    int array3[] = {1, 27, 30, 4};
    assert(sumaArr(array1,4)==10);
    assert(sumaArr(array2,5)==28);
    assert(sumaArr(array3,4)==62);
}


int main(void){

    test_sumaArr(); //TEST

    int tam=0;

    tam=pedir_tamanio();

    int array[tam];

    completar_Arreglo(array,tam);

    int elementos_suma=sumaArr(array,tam);

    printf("La suma de sus elementos es: %d",elementos_suma);
    return 0;

}