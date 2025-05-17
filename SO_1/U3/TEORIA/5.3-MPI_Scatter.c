#include <mpi.h>
#include <stdio.h>

void main(int argc, char** argv) {
    int rankProc, sizeComm, scattered_data;
    int arr[4]={39,72,129,42};

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeComm);
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    
    MPI_Scatter(&arr,1,MPI_INT,&scattered_data,1,MPI_INT,0,MPI_COMM_WORLD);

    printf("proceso recibio %d\n", scattered_data);

    MPI_Finalize();
}