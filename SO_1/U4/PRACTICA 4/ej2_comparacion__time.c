#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000000  // 100 millones

int main() {
    double *arr = malloc(sizeof(double) * N);
    if (arr == NULL) {
        printf("No se pudo asignar memoria\n");
        return 1;
    }

    // Inicialización
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        arr[i] = (double)i;
    }

    double sum_sec = 0.0, sum_red = 0.0, sum_mutex = 0.0;
    double t_start, t_end;

    // ------------------ SECUENCIAL ------------------
    t_start = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        sum_sec += arr[i];
    }
    t_end = omp_get_wtime();
    printf("Secuencial:   suma = %.2f | tiempo = %.4f s\n", sum_sec, t_end - t_start);

    // ------------------ REDUCTION ------------------
    t_start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_red)
    for (int i = 0; i < N; i++) {
        sum_red += arr[i];
    }
    t_end = omp_get_wtime();
    printf("Reducción:    suma = %.2f | tiempo = %.4f s\n", sum_red, t_end - t_start);

    // ------------------ MUTEX ------------------
    omp_lock_t lock;
    omp_init_lock(&lock);
    t_start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        omp_set_lock(&lock);
        sum_mutex += arr[i];
        omp_unset_lock(&lock);
    }

    t_end = omp_get_wtime();
    omp_destroy_lock(&lock);
    printf("Con mutex:    suma = %.2f | tiempo = %.4f s\n", sum_mutex, t_end - t_start);

    free(arr);
    return 0;
}
