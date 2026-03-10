// c) 
#include <stdio.h>

int main() {
    int* punt , i;
    int x[] = {1, 2, 3, 4, 5};
    punt = x;
    *punt = 9;   //x[0]=9
    for (i = 0; i < 5; i++)
    printf("%d, ", x[i]);   //9,2,3,4,5
    return 0;
}