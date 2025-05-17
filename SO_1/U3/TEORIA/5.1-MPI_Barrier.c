#include <mpi.h>
#include <stdio.h>


void main(int argc, char** argv) {
    int my_id;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_id);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("MPI BARRIER:%i",my_id);

    MPI_Finalize();
}

// sudo apt install libopenmpi-dev open mpi-doc

// mpicc a.c -o binario
// mpirun -np (nro core) ./binario