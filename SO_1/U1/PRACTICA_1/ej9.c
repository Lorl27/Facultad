#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>

// Ej. 9. Complete el c´odigo para capturar la se˜nal al presionar Ctrl-C.


void INThandler(int);


int main(void){
    
    signal(SIGINT,INThandler);

    while(1){
        sleep(10);
    }
}

void INThandler(int sig){
    char c;

    signal(SIGINT,INThandler);

    printf("OUCH, did you hit Ctrl-C?\n"
    "Do you really want to quit? [y/n] ");
    c = getchar();

    if(c == 'y' || c == 'Y'){
        exit(0);
    }
    else{
        signal(SIGINT,SIG_IGN);
        getchar();
        printf("ok. no salgas");
        exit(0);
    }
}