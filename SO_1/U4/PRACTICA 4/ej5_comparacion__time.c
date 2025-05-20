#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500  // Cambiá a 200, 500 o 1000 para probar distintos tamaños

int A[N][N], B[N][N], BT[N][N], C_seq[N][N], C_par[N][N];

// Inicializa matrices A y B con números aleatorios
void inicializar_matrices() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
}

// Transpone B y guarda en BT
void transponer_B() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            BT[j][i] = B[i][j];
}

// Multiplicación secuencial A × B
void multiplicar_secuencial() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C_seq[i][j] = 0;
            for (int k = 0; k < N; k++)
                C_seq[i][j] += A[i][k] * B[k][j];
        }
}

// Multiplicación paralela A × B
void multiplicar_paralelo() {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C_par[i][j] = 0;
            for (int k = 0; k < N; k++)
                C_par[i][j] += A[i][k] * B[k][j];
        }
}

// Verifica si las matrices C_seq y C_par son iguales
int verificar_igualdad() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (C_seq[i][j] != C_par[i][j])
                return 0;
    return 1;
}

int main() {
    inicializar_matrices();

    double t1 = omp_get_wtime();
    multiplicar_secuencial();
    double t2 = omp_get_wtime();

    double t3 = omp_get_wtime();
    multiplicar_paralelo();
    double t4 = omp_get_wtime();

    printf("Tiempo secuencial: %.4f segundos\n", t2 - t1);
    printf("Tiempo paralelo:   %.4f segundos\n", t4 - t3);

    if (verificar_igualdad())
        printf("✅ Las matrices resultantes son iguales.\n");
    else
        printf("❌ Las matrices NO coinciden.\n");

    return 0;
}
