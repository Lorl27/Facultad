#include <stdio.h>
#include <math.h>
#include <ieee754.h>

int main(){
    float a=NAN, b=INFINITY;
    printf("%f %f\n",a,b);
    
    union ieee754_float myfloat;
    myfloat.f = INFINITY;
    printf("Signo: %x\n", myfloat.ieee.negative);
    printf("Exponente: %x\n", myfloat.ieee.exponent);
    printf("Mantisa: %x\n", myfloat.ieee.mantissa);

    union ieee754_double mydouble;
    mydouble.d = NAN;
    printf("Signo: %x\n", mydouble.ieee.negative);
    printf("Exponente: %x\n", mydouble.ieee.exponent);
    printf("Mantisa (b51 a b32): %x\n", mydouble.ieee.
    mantissa0);
    printf("Mantisa (b31 a b0): %x\n", mydouble.ieee.
    mantissa1);
    return 0;
}