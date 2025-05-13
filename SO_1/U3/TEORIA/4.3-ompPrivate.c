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


int main(){

    int i = 1;
    #pragma omp parallel private(i) //si uso firstprivate(i) i va a tomar el valor global
    {
        printf("Thread %d: i = %d\n",omp_get_thread_num(),i);
        i = 1000;
        printf("private interna i = %d\n",i);
    }
    printf("private i = %d\n",i);

    return 0;
}