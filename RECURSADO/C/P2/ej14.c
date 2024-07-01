// Ejercicio 14. Escriba un programa que lea enteros hasta que se ingrese un número negativo
// y posteriormente imprimir qué valor entre 0 y 99 se ingresó más veces.

#include <stdio.h>

int validacion_num(int *array, int entero){
    int index=0;
    while(entero>=0 &&index<100){
        printf("ingrese un numero. negativo para finalizar: ");
        scanf("%d",&entero);
        if(entero>=0){
        array[index]=entero;
        index++;}
    }
    return index;
}

void comparacion_numeros(int *array,int tam){
    int index_mayor=0,contador_mayor=0;

    for(int x=0;x<tam;x++){

        int contador=1;

        for(int y=x+1;y<tam;y++){
            if(array[x]==array[y]){
                contador++;
            }
        }
        if(contador>contador_mayor){
            contador_mayor=contador;
            index_mayor=x;
        }
    }
    
    printf("El número que se ingreso más veces fue: %d, en total: %d veces.",array[index_mayor],contador_mayor);
}

int main(void){
    
    int entero=0;
    int array[100]={0}; //Inicializamos los valores.

    int tam=validacion_num(array,entero);

    comparacion_numeros(array,tam);
    
    return 0;
}