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
    int sum = 0;
    int val = 1;
    #pragma omp parallel for reduction(+: sum)
        for(int i = 0; i < 15; i++){
            sum = sum + val;
            printf("sum = %d\n",sum);
        }
        
    printf("suma = %d\n",sum);



    return 0;
}