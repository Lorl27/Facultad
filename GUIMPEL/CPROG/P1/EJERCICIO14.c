// Ejercicio 14. Escriba un programa que lea enteros hasta que se ingrese un número negativo
// y posteriormente imprima qué valor entre 0 y 99 se ingresó más veces.

#include <stdio.h>

int main(){
    int num;
    int numeros[100]={0}; // Inicializamos el arreglo en 0, todos tendran ese valor 0x100
    do{
        printf("ingrese un numero:\n");
        scanf("%d",&num);

        if (num>= 0 && num<=99) {
            numeros[num]++; // Incrementa el conteo del número ingresado. sirve pARA regiatro,
            //ya q numeros={0..0},numeros[5]=0,numeros[5]++=1...={o..o...1}
        }}
        while(num>=0);
    
// Encontrar el número que se ingresó más veces
    int max_repeticiones = 0;
    int num_mas_repetido = 0;

    for (int x=0;x<100;x++) {
        if (numeros[x] > max_repeticiones) {
            max_repeticiones=numeros[x];
            num_mas_repetido=x;
        }
    }

    printf("El número más repetido entre 0 y 99 es: %d\n", num_mas_repetido);

    return 0;

}