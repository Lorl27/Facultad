#include <stdio.h>
#include <math.h>
int main() {
    double a = 0.1;
    double b = 0.2;
    double c = 0.3;
    printf("a + b = %.17f\n", a + b);
    printf("c = %.17f\n", c);
    if (a + b == c)
    printf("Son iguales\n");
    else
    printf("No son iguales\n");
    if (fabs((a + b)- c) < 1e-15)
    printf("Son aproximadamente iguales\n");
    return 0;
}