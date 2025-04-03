#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(){
    const char* prog="test.out"; 
    
    while(1){
        pid_t pid = fork();
        if (pid == 0){
            execl(prog,prog,NULL);
        }
        else{
            sleep(2);
        }
    }
    return 0;
}