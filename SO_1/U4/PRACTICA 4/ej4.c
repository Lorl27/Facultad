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


#define N 100000000

int tomar_val(long int n){

    if(n <= 2)  return 0;

    int raiz = ((int) (sqrt(n))) +1;

    for(int i = 2; i < raiz; i++) {
        if(n % i == 0) {
            return 0;
        }
    }
    
    
    return 1;
}


int main(){

    long int p;
    int r;
    printf("ingresa nro:\t");
    scanf("%ld",&p);

    #pragma omp parallel num_threads(4)
    {
    r=tomar_val(p);

    }

    if(r==0) printf(" %ld no primo\n",p);
    else printf("primo!");
    
    return 0;
}
