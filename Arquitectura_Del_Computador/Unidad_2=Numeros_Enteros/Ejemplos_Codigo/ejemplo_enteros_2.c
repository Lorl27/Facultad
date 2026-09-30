#include <stdio.h>

int main() {
    int a = 2000000000;
    int b = 2000000000;
    
    printf("a: %d, b: %d\n", a, b);

    int promedio = (a + b) / 2;

    printf("Promedio: %d\n", promedio);
    
    int promedio2 = a/2 + b/2;
    
    printf("Promedio: %d\n", promedio2);
    
    long long promedio3 = (((long long)a + b) / 2);
    
    printf("Promedio: %d\n", promedio3);

    return 0;
}
