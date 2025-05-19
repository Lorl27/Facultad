// Ej. 5 (Multiplicaci´on de Matrices). Implemente en OpenMP la multiplicaci´on de dos matrices en
// paralelo. Una versi´on secuencial es:
#include <stdio.h>
#include <stdlib.h>

#define N 200

int A[N][N], B[N][N], C[N][N];

void mult(int A[N][N], int B[N][N], int C[N][N])
{
    int i, j, k;
#pragma omp for
    for (i = 0; i < N; i++)

        for (j = 0; j < N; j++)

            for (k = 0; k < N; k++)
#pragma omp critical 
{
                C[i][j] += A[i][k] * B[k][j];
}

}

int main()
{
    int i, j;
#pragma omp parallel num_threads(4)
    {
#pragma omp for
        for (i = 0; i < N; i++)
        {

            for (j = 0; j < N; j++)
            {
                A[i][j] = random() % 1000;
                B[i][j] = random() % 1000;
            }
        }
        mult(A, B, C);
    }

    return 0;
}

// a) Compare la performance con la soluci´on secuencial para matrices cuadradas de tama˜no 200x200,
// 500x500 y 1000x1000. ¿Qu´e relaci´on aproximada puede inferir entre los tiempos en uno y otro caso?

// b) Si se cambia el orden de los ´ındices, ¿se puede mejorar el rendimiento? ¿Por qu´e?
// porque si.

// c) Si tuviese que computar la multiplicaci´on de A × BT , ¿se puede mejorar el rendimiento? ¿Por qu´e?
// NO! complemento de B es peor. tenes qw buscar ña inversa.