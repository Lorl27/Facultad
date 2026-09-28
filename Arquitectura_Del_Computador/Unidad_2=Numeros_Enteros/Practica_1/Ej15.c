// 15) Implemente una funci´on en lenguaje C:
// int is_one(long n, int b);
// que indique si el bit b-´esimo del entero n es 1 o 0.
// Ayuda: Pensar en las propiedades de los operadores de bits.

#include <stdio.h>
#include <stdlib.h>

// Devuelve 0 si el b-ésimo bit es de n es 0,
//devuelve 1 si es 1.
int is_one(long n, int b){
    long mascara= n>>b;
    int resultado= mascara & 1;

    return resultado;
}

/* Forma alternativa:
int is_one(long n, int b){
    long mascara = 1L << b;
    return (n & mascara) != 0;
}
*/

int main(void){
    long a = 0b1001;
    long b = 0b10001110;

    printf("El 1-esimo bit de %d es: %d\n",a,is_one(a,1)); //0
    printf("El 3-esimo bit de %d es: %d\n",a,is_one(a,3)); //1
    printf("El 4-esimo bit de %d es: %d\n",a,is_one(b,4)); //1

    return 0;
}