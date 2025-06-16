// Ej.14(Producto distribuido).El siguiente fragmento de c´odigo permite calcular el producto de una matriz cuadrada por un vector, ambos de la misma dimensi´on
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


#define N  100
    int main(int argc, char **argv) {
    int i, j;
    int A[N][N], v[N], x[N];
    MPI_Init(&argc, &argv);
    /*Leer A y v*/
#pragma omp parallel
{
#pragma omp for
            for (i = 0; i < N; i++) {
                x[i] = 0;
                for (j = 0; j < N; j++)
                    x[i] += A[i][j] * v[j];
            }
            /*Escribir x */

            
}
return 0;
}


        // a) Escriba un programa MPI que realice el producto en paralelo, teniendo en cuenta que el proceso 0 lee
        // la matriz A y el vector v, realiza una distribuci´on de A por bloques de filas consecutivas sobre todos los
        // procesos y env´ıa v a todos los procesos. Asimismo, al final el proceso 0 debe obtener el resultado.
        // b) Calcular el speed up y la eficiencia