#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    
    pid_t pid=fork();

    int mem;
    char string[200];

    if(pid==0){
        const char* ejec = strtok(string,"\0");
        execl(ejec,ejec,NULL);
        sleep(2);
        
    }
    else{
        fgets(string,200,stdin);
        
        wait(&mem);
    }
    return 0;
}
