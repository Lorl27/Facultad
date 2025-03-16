// 2. Selección
// Ejercicio 4. Determinar en qué estado está el agua en función de su temperatura:
// si es negativa el estado será sólido, si es menor que 100 será líquido y si es mayor que 100 será gas.
// El valor de la temperatura deberá ingresarse.

#include <stdio.h>
#include <assert.h>

void estado_temperatura(float temp){
    if (temp<0){
        printf("sólido");
    }
    else if (temp<100){
        printf("líquido");
    }
    else{
        printf("gaseoso");
    }
    
}

int main(){
    float temperatura;
    printf("La siguiente funcion le permitirá determinar el estado del agua, según su temperatura:\n");
    printf("Inserte la temperatura a continuación: ");

    scanf("%f",&temperatura);
    
    printf("El estado del agua con temperatura %0.2f es: ",temperatura);
    estado_temperatura(temperatura);
    return 0;
}