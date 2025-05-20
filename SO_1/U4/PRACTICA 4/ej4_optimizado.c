#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int es_primo(long n) {
    if (n <= 1) return 0;

    int bandera= 1;
    long raiz = (long)sqrt(n) + 1;

    #pragma omp parallel for shared(bandera)
    for (long i = 2; i <= raiz; i += 2) {
        if (!bandera) continue;  // Otro hilo ya encontró un divisor

        if (n % i == 0) {
            #pragma omp atomic write
            bandera = 0;
        }
    }

    return bandera;
}

int main() {
    long p;
    printf("Ingrese un número: ");
    scanf("%ld", &p);

    double start = omp_get_wtime();
    int r = es_primo(p);
    double end = omp_get_wtime();

    if (r)
        printf("%ld es primo\n", p);
    else
        printf("%ld no es primo\n", p);

    printf("Tiempo: %.4f segundos\n", end - start);
    return 0;
}
