// Ej. 5 (Multiplicaci´on de Matrices). Implemente en OpenMP la multiplicaci´on de dos matrices en
// paralelo. Una versi´on secuencial es:
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 200

int A[N][N], B[N][N], C[N][N];

void mult(int A[N][N], int B[N][N], int C[N][N]) {
    int i, j, k;

    // Inicializamos la matriz C en cero
    #pragma omp for
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            C[i][j] = 0;

    // Multiplicación de matrices
    #pragma omp for collapse(2)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int i, j;

    // Inicializamos A y B en paralelo
    #pragma omp parallel for collapse(2)
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % 1000;
            B[i][j] = rand() % 1000;
        }

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        mult(A, B, C);
    }

    double end = omp_get_wtime();
    printf("Tiempo: %.4f segundos\n", end - start);

    return 0;
}


//* a) Compare la performance con la soluci´on secuencial para matrices cuadradas de tama˜no 200x200,
//* 500x500 y 1000x1000. ¿Qu´e relaci´on aproximada puede inferir entre los tiempos en uno y otro caso?
// El tiempo debería crecer cúbicamente: O(N^3), porque cada posición en C[i][j] hace N multiplicaciones y sumas.

// Comparando:
// 200×200 → 200^3 = 8 × 10^6 ops
// 500×500 → 125 × 10^6 ops (más de 15 veces mayor)
// 1000×1000 → 10^9 ops (más de 100 veces mayor)


//* b) Si se cambia el orden de los ´ındices, ¿se puede mejorar el rendimiento? ¿Por qu´e?
// Sí.
// El acceso a la memoria importa: en C, las matrices están en orden por filas (row-major order), así que acceder en orden A[i][k] y B[k][j] es mejor que desordenado. Si cambiaras a B[j][k] podrías afectar la localidad de caché y empeorar la performance.

//* c) Si tuviese que computar la multiplicaci´on de A × BT , ¿se puede mejorar el rendimiento? ¿Por qu´e?
// Sí, si transponés B explícitamente antes de la multiplicación.
// Acceder a B[k][j] es peor que acceder a BT[j][k], porque podrías forzar saltos en memoria (cache misses).
// Si computás la transpuesta BT[j][k] = B[k][j], y luego hacés A[i][k] * BT[j][k], el acceso es más alineado y se puede mejorar la cache.