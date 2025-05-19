#include <mpi.h>
#include <stdio.h>

void main(int argc, char** argv) {
    int rank,value=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank==0){ //proceso inicial
        printf("nuro para broadcat:\n");
        scanf("%i",&value);
    }else{
        printf("proceso %d, antes de MPI_Bcast %d\n", rank, value);
    }

    // ()- tam  - (int) - a q proceso voy - ()
    
    MPI_Bcast(&value,1,MPI_INT,0,MPI_COMM_WORLD); //se bloquean

    printf("proceso %d, dsp de MPI_Bcast %d\n", rank, value);

    MPI_Finalize();
}