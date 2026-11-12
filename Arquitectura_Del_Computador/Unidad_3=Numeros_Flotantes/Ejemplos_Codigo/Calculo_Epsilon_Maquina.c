//Compilar con -lquadmath

#include <stdio.h>
#include <float.h>
#include <quadmath.h>
int main(){
    float x = 1.0;
    double y = 1.0;
    long double z =1.0;
    _Float128 w = 1.0;
    int n = 0;
    char buf[128];
    while ((float)1.0 + (x * (float)0.5) > (float)1.0){
    ++n;
    x *= 0.5;
    }
    printf("Float: ´ Epsilon de m´aquina: 2^(-%d)=%g\n", n, x);
    n = 0;
    while (1.0 + (y * 0.5) > 1.0){
    ++n;
    y *= 0.5;
    }
    printf("Double: ´ Epsilon de m´aquina: 2^(-%d)=%g\n", n, y);
    n = 0;
    while (1.0 + (z * 0.5) > 1.0){
    ++n;
    z *= 0.5;
    }
    printf("Long double: ´ Epsilon de m´aquina: 2^(-%d)=%Lg\n",
    n, z);
    n = 0;
    while (1.0 + (w * 0.5) > 1.0){
    ++n;
    w *= 0.5;
    }
    quadmath_snprintf(buf, sizeof buf, "%.4Qg", w);
    printf("_Float128: ´ Epsilon de m´aquina: 2^(-%d)=%s\n", n,buf);
    return 0;
}