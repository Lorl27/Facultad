// Compilar con la opción -lquadmath
#include <quadmath.h>
#include <stdio.h>

int main(void) {
    __float128 x = 1.0Q / 3.0Q;  // Q indica literal cuádruple
    char buf[64];
    quadmath_snprintf(buf, sizeof buf, "%.36Qg", x);
    printf("x = %s\n", buf);
    return 0;
}
