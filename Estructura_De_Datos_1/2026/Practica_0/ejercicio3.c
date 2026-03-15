#include <stdio.h>
#include <stdlib.h>

void set_int(int * nro){
    *nro = (*nro != 0) ? 1 : 0;
}

int main(){
    int * nro1=malloc(sizeof(int));
    int * nro2=malloc(sizeof(int));

    *nro1=5;
    *nro2=0;


    set_int(nro1);
    set_int(nro2);

    free(nro1);
    free(nro2);

    return 0;

}