#include <stdio.h>
#define PI 3.14159
#define VOL_ESFERA(radio) ((4.0/3.0)*(PI)*(radio)*(radio)*(radio))

int main(){
    printf("%-10s %-15s\n", "Radio", "Volumen");
    printf("-------------------------\n");
    for(int rad=1;rad<=10;rad++){
        double calulo_vol=VOL_ESFERA(rad);
        printf("%-10d %-15.2f \n",rad,calulo_vol);
    }
    return 0;
}