#include <stdio.h>

int fib_recursivo(int n);

int fib_recursivo(int n) {
    if (n <= 1)
        return n;
    return fib_recursivo(n - 1) + fib_recursivo(n - 2);
}

int main() {
    int n;
    int resultado;
    printf("Ingrese un numero: ");
    scanf("%d", &n);
    resultado = fib_recursivo(n);
    printf("Resultado recursivo: fib(%d) = %d\n", n, resultado);

    return 0;
}

