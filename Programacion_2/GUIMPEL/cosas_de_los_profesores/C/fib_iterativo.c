#include <stdio.h>
int fib_iterativo(int n);

int fib_iterativo(int n) {
    int a = 0, b = 1;
    int i = 0;
    while (i < n) {
        int temporal = a;
        a = b;
        b = temporal + b;
        i++;
    }
    return a;
}

int main() {
    int n;
    int resultado;
    printf("Ingrese un numero: ");
    scanf("%d", &n);
    resultado = fib_iterativo(n);
    printf("Resultado iterativo con int: fib(%d) = %d\n", n, resultado);

    return 0;
}

