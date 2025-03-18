//f )

#include <stdio.h>

int *direccion_local(int x) {
    return &x;                      //ERROR - NO SE PUEDE RETORNAR UNA DIR LOCAL!
}

int main() {
    int *ptr = NULL;
    ptr = direccion_local (2);  //COMO ES LOCAL, DSP SERÁ SEGMENTION FAULT
    printf("%d\n", *ptr);
    return 0;
}