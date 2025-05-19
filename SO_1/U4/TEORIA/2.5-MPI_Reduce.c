#include <mpi.h>
#include <stdio.h>

void main(int argc, char** argv) {
    int rankProc;

    MPI_Init(&argc, &argv);
 
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);

    int result_r=0;

    MPI_Reduce(&rankProc, &result_r, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);

        if(rankProc==0){
    printf("suma de todos los ranks: %d\n", result_r);}

    MPI_Finalize();
}