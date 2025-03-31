//  e) Con fork(), cree dos procesos y haga que el hijo termine (con exit() o retornando del main) y que
//  el padre duerma inde nidamente sin hacer wait(). Como aparece el hijo en la tabla de procesos?
//  Por que sigue existiendo?

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

int main(){
    pid_t pid=fork();

    if(pid==0){
        exit(0);
    }
    else{
        while(1){
            sleep(1);
            }
    }
    return 0;
    
}


//** Cuando el hijo termina y el padre no llama a wait(), el proceso hijo queda en estado zombie, 
// * en la tabla de procesos aparecerá como <defunct> 
//* Si el padre muere, pasará a tener de parent a Init.