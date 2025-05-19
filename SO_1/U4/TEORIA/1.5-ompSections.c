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


#include <omp.h>

#define NTHREADS 5

int main(){
    #pragma omp parallel sections num_threads(NTHREADS)
    {

        #pragma omp section
        {
            printf("Thread id %d (section 1)\n",omp_get_thread_num());


        }
        #pragma omp section
        {
            printf("Thread id %d (section 2)\n",omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Thread id %d (section 3)\n",omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Thread id %d (section 4)\n",omp_get_thread_num());
        }


    }

    return 0;
}