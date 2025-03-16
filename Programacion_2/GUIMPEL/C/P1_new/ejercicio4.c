//? 2. Selección

// Ejercicio 4: Determinar en qué estado está el agua en función de su temperatura: si es negativa el estado será sólido, si es menor que 100 será líquido y si es mayor que 100 será gas.
// El valor de la temperatura deberá ingresarse.

#include <stdio.h>

//! En función de su temperatura, nos imprimirá su estado.
void temperatura_estado(const float a){
    if(a < 0){
        printf("El agua está en estado sólido.\n");
    }else if(a > 100){
        printf("El agua está en estado gaseoso.\n");
    }else{
        printf("El agua está en estado líquido.\n");
    }
}

int main(){
    float nro;
    printf("Ingrese la temperatura a continuacion:\n");
    scanf("%f",&nro);

    temperatura_estado(nro);

    return 0;
}