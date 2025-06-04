// Ej. 10 (Suma Distribuida). Implemente en MPI un programa distribuido que compute la suma de
// un array distribuyendo segmentos del mismo.
// Su soluci´on debe ser robusta si var´ıa el tama˜no del array
// y/o la cantidad de procesos involucrados.
// Corra en programa con distintas cantidad de procesos: 4, 8, y 16.

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(int argc, char** argv) {

    srand(time(NULL));

    int num_procs, my_id;
    int suma=0,leng=0;
    int *array;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&my_id);

    leng=my_id;
    printf("id: %d\n",my_id);
    array=malloc(sizeof(int)*leng);
    //printf("aaar: %ls -- \n",array);
    
    printf("leng: %d\n",leng);

    for(int x=0;x<leng;x++){
         array[x]=  x * (2 + rand() % (10 - 2 + 1));
         printf("%d\n",array[x]);
         suma+= array[x];
     }

    printf("SUMA: %d\n", suma);

    free(array);
    MPI_Finalize();

    
}

// sudo apt install libopenmpi-dev open mpi-doc

// mpicc a.c -o binario
// mpirun -np (nro core) ./binario