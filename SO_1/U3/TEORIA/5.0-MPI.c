#include <mpi.h>
#include <stdio.h>


void main(int argc, char** argv) {
    int num_procs, my_id;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    printf("hui, proceso %d/%d\n",my_id,num_procs);
    MPI_Finalize();
}

// sudo apt install libopenmpi-dev open mpi-doc

// mpicc a.c -o binario
// mpirun -np (nro core) ./binario