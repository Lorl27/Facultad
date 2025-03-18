// a)

#include <stdio.h>

int main() {
    int* punt;  //creamos puntero
    int x = 7, y = 5;
    punt = &x;  //el puntero tiene dir de memoria de x=7
    *punt = 4;  //ahora x=4
    printf("%d %d", x, y);  //4 , 5
    return 0;
}

