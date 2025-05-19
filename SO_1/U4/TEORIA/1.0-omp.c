#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>


#include <omp.h>  //gcc -fopenmp 4.0-omp.c -o omp_program


int main(){

    #pragma omp parallel //barrier hace que cada thread espere a que el resto termine 
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();

        printf("Thread id %d, num threads: %d\n",id,nt);


    }


    return 0;
}