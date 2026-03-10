
#include <stdio.h>

#define SUM(x,y) ((x)+(y))

int main(){

    int x=4; int y=9;
    int suma=SUM(x,y);
    printf("La suma de %d con %d es: %d",x,y,suma);


    return 0;
}