// 3. Implemente una funci ́on set in(int *) que toma un puntero a un entero, y reemplaza el entero
// apuntado por un 1 si el entero apuntado era diferente a 0, y 0 en caso contrario


#include <stdio.h>

void set_in(int * puntero){
    if(*puntero!=0){
        *puntero=1;
    }
    else{
        *puntero=0;
    }
}

int main(){
    int a=5 , b=0;

    int *p=&a, *q=&b;

    printf("Punteros,antes de la función: \n\n P:%d \n Q:%d\n",*p,*q);

    set_in(p);
    set_in(q);

    printf("Punteros,después de la función: \n\n P:%d \n Q:%d\n",*p,*q);

    return 0;
}