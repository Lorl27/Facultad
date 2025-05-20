// Ej. 4 (Primalidad). Escriba utilizando OpenMP una funci´on que verifique si un entero es primo
// (buscando divisores entre 2 y √N ). Su soluci´on deber´ıa andar igual o m´as r´apido que una versi´on secuencial
// que “corta” apenas encuentra un divisor. Escriba su funci´on para tomar un long, i.e. un entero de 64
// bits1, y aseg´urese de probarla con n´umeros grandes (incluyendo primos, semiprimos, y pares).

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

//0: primo , 1: no primo
int tomar_val(long int n){

    if(n < 2)  return 1;

    int bandera=0;

    long int raiz = (int) sqrt(n);

    #pragma omp parallel for
    for(long int i = 2; i <= raiz; i++) {
        if(n % i == 0) {
            #pragma omp critical
            {
                bandera=1; //No primo -> E divisor.
            }
        }
    }
    
    
    return bandera;
}


int main(){

    long int p;

    printf("ingresa nro:\t");
    scanf("%ld",&p);

    int r=tomar_val(p);

    if(r) printf(" %ld no primo\n",p);
    else printf("primo!");
    
    return 0;
}
