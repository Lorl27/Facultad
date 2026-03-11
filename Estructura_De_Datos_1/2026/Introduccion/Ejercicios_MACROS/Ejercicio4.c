#include <stdio.h>
#define MININUM2(x,y) ( ((x)<(y))?(x):(y) )

int main(){
    double numero_1;
    double numero_2;

    printf("Escriba el primer nro: \n");
    scanf("%lf", &numero_1);

    printf("Escriba el segundo nro: \n");
    scanf("%lf", &numero_2);

    printf("El nùmero màs pequeño entre [%.2f,%.2f] es %.2f",numero_1,numero_2,MININUM2(numero_1,numero_2));

    return 0;
}

