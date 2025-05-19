#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define N 100000000

int main() {
    int *arr = malloc(N * sizeof(int));
    if (arr == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    // Llenar arreglo con valores
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100000 - 50000; // valores entre -50000 y 49999
    }

    int min_sec = INT_MAX;
    double t_start = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        if (arr[i] < min_sec)
            min_sec = arr[i];
    }
    double t_end = omp_get_wtime();
    printf("Secuencial: mínimo = %d | tiempo = %.4f s\n", min_sec, t_end - t_start);

    int min_par = INT_MAX;
    t_start = omp_get_wtime();
    #pragma omp parallel for reduction(min:min_par)
    for (int i = 0; i < N; i++) {
        if (arr[i] < min_par)
            min_par = arr[i];
    }
    t_end = omp_get_wtime();
    printf("Paralelo:    mínimo = %d | tiempo = %.4f s\n", min_par, t_end - t_start);

    free(arr);
    return 0;
}
