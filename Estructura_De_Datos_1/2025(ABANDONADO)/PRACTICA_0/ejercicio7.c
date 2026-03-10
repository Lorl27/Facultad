// 7. Escriba un programa que reserve un espacio de memoria de 100 bytes, y luego lib ́erelo dos veces. ¿Se
// produce alg ́un error?

#include <stdlib.h>
#include <stdio.h>

int main(){

    int* p =malloc(sizeof(int)*100);

    free(p);
    free(p);

    return 0;

}


//Si! habrá un tipo de error : DANGLING REFERENCE.