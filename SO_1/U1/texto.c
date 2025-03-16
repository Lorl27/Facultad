#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(){
    char buffer[1024];
    char path[]="txta.txt";
    int abrir =open(path,O_RDONLY);


    int num_r=read(abrir,buffer,1024); //caracteres a leer :D

    buffer[num_r] = '\0';

    printf("%s\n",buffer);

    return 0;
}