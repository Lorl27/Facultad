#include <stdio.h>

long fib_iterativo(int n);

long fib_iterativo(int n) {
    long a = 0, b = 1;
    int i = 0;
    while (i < n) {
        long temporal = a;
        a = b;
        b = temporal + b;
        i++;
    }
    return a;
}

int main() {
    int n;
    long resultado;
    printf("Ingrese un numero: ");
    scanf("%d", &n);
    resultado = fib_iterativo(n);
    printf("Resultado iterativo con long: fib(%d) = %ld\n", n, resultado);

    return 0;
}

