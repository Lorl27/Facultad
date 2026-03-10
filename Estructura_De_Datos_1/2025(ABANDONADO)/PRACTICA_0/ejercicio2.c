
// 2: Implemente una funci´on void set first(int []) que ponga en cero el primer elemento del arreglo
// recibido. Verifique desde la funci´on llamante que efectivamente modifica este valor. ¿Por qu´e pasa esto?
// ¿No llama a la funci´on por valor?

#include <stdio.h>


void set_first (int a[]){  //== int *a
    a[0]=0;                //== *a=0
}

int main(){

    int array[]={1,2,3};

    printf("Primer elemento del array, antes de la función: %d \n", array[0]);

    set_first(array);

    printf("Primer elemento del array, después de la función: %d \n", array[0]);

    return 0;

}


//* RTA: Al pasar el array como parámetro, lo hace es tomar la dirección de memmoria del primer elemento del mismo, como si fuera un puntero.