
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

// Ej. 8. El siguiente programa intenta corregir con gracia una divisi´on por cero, atrapando la se˜nal
// correspondiente (SIGFPE) y modificando el denominador de la divisi´on en ese caso.

int denom = 0;

void handler(int s) { 
    printf("ouch!\n");
    denom = 1; 
}

int main() {
    int r;

    signal(SIGFPE, handler);

    r = 1 / denom;

    printf("r = %d\n", r);

    return 0;
}
// // ¿Qu´e pasa al correr el programa? ¿Por qu´e?
// nunca se actualiza denom (global=0 y local=1)