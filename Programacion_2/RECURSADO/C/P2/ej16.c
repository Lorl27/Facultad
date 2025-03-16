// Ejercicio 16. Escriba una función sumaAlt que tome un arreglo de enteros junto con la longitud del mismo 
//y devuelva el producto de los elementos cuyos índices son pares.

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


int sumaAlt(int *array,int size){
    int prod=1;
    for(int x=0;x<size;x++){
        if(x%2==0){
        prod*=array[x];}
    }
    return prod;
}

void test_sumaAlt(void){
    int array1[] = {1, 2, 3, 4};
    int array2[] = {10, 2, 3, 4,9};
    int array3[] = {1, 27, 30, 4};
    assert(sumaAlt(array1,4)==3);
    assert(sumaAlt(array2,5)==270);
    assert(sumaAlt(array3,4)==30);
}


int main(void){

    test_sumaAlt(); //TEST

    int tam=0;

    tam=pedir_tamanio();

    int array[tam];

    completar_Arreglo(array,tam);

    int elementos_prod_par=sumaAlt(array,tam);

    printf("El producto de sus elementos cuyos índiceds son pares es: %d",elementos_prod_par);
    return 0;

}