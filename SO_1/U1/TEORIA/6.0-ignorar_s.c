#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// void ignorar(){
//     printf("ignorado\n");
//     //SIG_IGN
//     exit(0);
// }

int main(){
    signal(SIGTSTP,SIG_IGN);  //SIG_IGN nos dice que señal ignorar
    raise(SIGTSTP);  //Será ignorada esta señal al generarla (EL programa NO se detendrá)
    sleep(3);
    printf("La señAL fue ignorda con éxito!\n");
    return 0;
    
}

