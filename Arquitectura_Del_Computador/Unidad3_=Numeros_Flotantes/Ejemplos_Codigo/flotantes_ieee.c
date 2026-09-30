#include <stdio.h>
#include <ieee754.h>

int main(){
	union ieee754_float mif;
	mif.ieee.exponent = 128;
	mif.ieee.negative = 0;
	mif.ieee.mantissa = 0;
	printf("%f\n", mif.f);

	union ieee754_double mid;

    	mid.ieee.exponent = 1024;   // exponente con bias 1023 → representa 2.0
    	mid.ieee.negative = 0;      // bit de signo = positivo
    	mid.ieee.mantissa0 = 0;     // mantisa (parte alta)
    	mid.ieee.mantissa1 = 0;     // mantisa (parte baja)

    	printf("%f\n", mid.d);
	return 0;
} 
