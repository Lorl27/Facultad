// Ejercicio 12. Escriba un programa que lea un arreglo a de 10 enteros y un entero n 
//e imprima
// el índice del arreglo a donde se encuentra n si n está presente en el arreglo, o -1 en caso
// contrario.

#include <stdio.h>

int main(){
    int a[10];
    int n;
    int bandera=-1;
    printf("Ingrese 10 enteros: \n");
    for(int x=0;x<10;x++){
        scanf("%d",&a[x]);
    }

    printf("Ingresa un numero cualquiera:\n");
    scanf("%d",&n);

    for(int x=0;x<10;x++){
        if(a[x]==n){
            bandera=x;
            break;
        }
    }

    if(bandera!=-1){
        printf(" el numero esta en el indice: %d\n",bandera);
    }
    else{printf("%d",bandera);}
    return 0;
}