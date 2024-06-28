// 2. Estructura For
// Ejercicio 3. Calcule mediante bucles for las siguientes sumatorias.

#include <stdio.h>
#include <assert.h>
#include <math.h>

double sumatoria_uno(void){
    double suma=0;
    for(double x=1;x<=100;x++){
        suma+=(1/x);
        printf("%lf \n",suma);
    }
    return suma;
}

double sumatoria_dos(void){
    double suma=0;
    for(double x=1;x<=30;x++){
        suma+=(1/x*x);
        printf("%lf \n",suma);
    }
    return suma;
}

double sumatoria_tres(void){
    double suma=0;
    for(double x=1;x<=25;x++){
        suma+=(1/pow(x,x));
        printf("%lf \n",suma);
    }
    return suma;
}

double sumatoria_cuatro(void){
    double suma=0;
    for(double x=2;x<=10;x++){
        suma+=(x+1)*x;
        printf("%lf \n",suma);
    }
    return suma;
}

void test_sumatorias(void){
    assert(fabs(sumatoria_uno() - 5.1873775) < 0.0001);
    assert(fabs(sumatoria_dos() - 30.0) < 0.0001);
    assert(fabs(sumatoria_tres() - 1.291286) < 0.0001); // Esperando que el resultado sea muy cercano a 1
    assert(fabs(sumatoria_cuatro() - 438.0) < 0.0001);
}

void validad_sum(int seleccion){
    switch(seleccion){
        case 1:
            sumatoria_uno();
            break;
        case 2:
            sumatoria_dos();
            break;
        case 3:
            sumatoria_tres();
            break;
        case 4:
            sumatoria_cuatro();
            break;
        default:
            printf("Esa sumatoria no existe.");
            break;
    }

}

int main(void){

    //test_sumatorias(); //TEST

    int seleccion;

    printf("Elige qué sumatoria prefieres: \n\n-1\n-2\n-3\n-4\n");
    scanf("%d",&seleccion);

    validad_sum(seleccion);

    return 0;
}