// Teniendo esto en cuenta, calculad la media entre los elementos de dos arrays. 
// Se pide para ello que imprimáis por pantalla los elementos de dos arrays y que 
// calculéis e imprimáis la media entre cada par de elementos.
// Para ello, cread en vuestro entorno de desarrollo un fichero llamado arrays_as_pointers.c, 
// e implementad en él lo siguiente (veréis que es el mismo programa que el de arrays básicos,
//  pero ahora tendréis que enviar el array en forma de puntero):

//     Una función que imprima por pantalla los elementos de un array de enteros: void print_array(int *array);

//     Una segunda función que calcule la media entre cada par de elementos de un array y que 
//     la vaya imprimiendo por pantalla: void calculate_average(int *array1, int *array2);.
//      Para la primera posición de cada array, sumará los dígitos y los dividirá por dos,
//       y ese resultado lo sacará por pantalla, y así con el resto de posiciones.

//     Una función main que declare e inicialice dos arrays de 10 enteros con los dígitos que queráis,
//      por ejemplo int array1[] = {1,5,7,3,12,...};, y 
//      que haga uso de la primera función para imprimir los arrays y de la segunda para calcular la media.

#include <stdio.h>
#include <stdlib.h>

void imprimir(int *array){
    
    for(int x=0;x<largo;x++){
        printf("\nEl array en la pos[%d]==%d\n",x,array[x]);
    }
}

void media(int *array1, int *array2){
    int largo=(sizeof(array1)/sizeof(array1[0]))*(sizeof(array2)/sizeof(array2[0]));
    for(int x=0,y=0;x<largo,y<largo;x++,y++){
        int resultado=(array1[x]+array2[x])/2;
        printf("%d la media \t",resultado);
    }
}

int main(){
    int t1,t2;

    printf("ingrese el tamaño del primer arreglo");
    scanf("%d",&t1);
    int array1[t1];

    printf("ingrese el tamaño del 2do arreglo");
    scanf("%d",&t2);
    int array2[t2];

    printf("rellenemos el 1er arreglo:\n");
    for(int x=0;x<t1;x++){
        printf("ingrese el contenido de la pos: %d",x+1);
        scanf("%d",&array1[x]);
    }

    printf("rellenemos el 2do arreglo:\n");
    for(int x=0;x<t2;x++){
        printf("ingrese el contenido de la pos: %d",x+1);
        scanf("%d",&array2[x]);
    }

    imprimir(array1);
    imprimir(array2);
    media(array1,array2);
    return 0;
}