//  h) Que pasa con los le descriptor de un proceso al hacer fork()? Y exec()?

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

    printf("MEMORIA INICIAL");

    pid_t pid=fork();

    printf("MEMORIA DSP DEL FORK");

    char path[]="../txta.txt";
    execl(path,path,NULL);

    printf("MEMORIA DSP DEL EXEC");

    return 0;
}



/*


Acción	Efecto en los FDs

fork()	Los FDs se heredan en el hijo y apuntan al mismo archivo en el kernel.
exec()	Los FDs siguen abiertos, salvo que tengan FD_CLOEXEC, en cuyo caso se cierran automáticamente.

*/