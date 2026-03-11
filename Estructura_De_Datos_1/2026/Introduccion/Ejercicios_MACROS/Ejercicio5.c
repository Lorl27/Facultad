
#include <stdio.h>
#define MININUM2(x,y) ( ((x)<(y))?(x):(y) )

#define MININUM3(x,y,z) MININUM2((x), MININUM2((y), (z)))



int main(){
    float nro1; float nro2; float nro3;

    printf("Digite su primer nro: \n");
    scanf("%f",&nro1);

    printf("Digite su segundo nro: \n");
    scanf("%f",&nro2);

    printf("Digite su tercer nro: \n");
    scanf("%f",&nro3);

    printf("El menor de los 3 nros (%.2f,%.2f,%.2f) es: %.2f",nro1,nro2,nro3,MININUM3(nro1,nro2,nro3));

    return 0;
}