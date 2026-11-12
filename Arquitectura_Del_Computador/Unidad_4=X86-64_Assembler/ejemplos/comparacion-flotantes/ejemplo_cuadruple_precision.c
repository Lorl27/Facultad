// Compilar con -lquadmath 
//
#include <stdio.h>
#include <quadmath.h>

int main()
{
    __float128 a = 3.1416Q;

    char buffer[128];

    quadmath_snprintf(buffer, sizeof(buffer), "%.36Qg", a);

    printf("%s\n", buffer);

    return 0;
}

