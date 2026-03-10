//b)

#include <stdio.h>

int main() {
    int* punt;
    int x = 7, y = 5;
    punt = &x; //7
    x = 4;
    punt = &y;  //5
    printf("%d %d", *punt , x);   //5 4
    return 0;
}