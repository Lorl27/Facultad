// 4. Implemente una funci ́on void swap(int *, int *) que dados dos punteros a variables, intercambie
// el contenido de las variables apuntadas.

#include <stdio.h> 

void swap(int *a, int *b){
    int temp=*b;
    *b=*a;
    *a=temp;
}

int main(){

    int a=5 , b=0;

    int *p=&a, *q=&b;

    printf("Punteros,antes de la función: \n\n P:%d \n Q:%d\n",*p,*q);

    swap(p,q);

    printf("Punteros,después de la función: \n\n P:%d \n Q:%d\n",*p,*q);


    return 0;
}