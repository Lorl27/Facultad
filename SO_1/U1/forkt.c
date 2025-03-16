#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>


int main(){
    
    pid_t pid= fork();
    if(pid==0){
        printf("hola, soy child y mi pid es:-- %d\n",getpid()); //pid hijo
        
    }
    else{
        printf("Hola, soy parent, y se pid del child: -- %d\n", getpid());
    }
    printf("%d\n", getpid()); //2do vuelta:pid hijo
    return  0;
}