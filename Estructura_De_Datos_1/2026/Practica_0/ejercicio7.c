#include <stdio.h>
#include <stdlib.h>

int main(){
    int * p=malloc(100);
    free(p);

    //si ponemos p=NULL, ya no saldria error ;)
    free(p);

    return 0;
}

/* Sì, tendremos un Dangling Pointer.*/