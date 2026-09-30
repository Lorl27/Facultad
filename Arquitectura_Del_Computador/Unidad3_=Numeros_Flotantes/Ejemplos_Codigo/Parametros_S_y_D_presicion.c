#include <stdio.h>
#include <float.h>

int main() {
    printf("=== SIMPLE PRECISION (float) ===\n");
    printf("Epsilon (FLT_EPSILON)= %.10e\n",FLT_EPSILON);
    printf("Min positivo normalizado
    = %.10e\n", FLT_MIN);
    printf("Min positivo (incluyendo subnormales) = %.10e\n",
    FLT_TRUE_MIN);
    printf("Max valor representable= %.10e\n", FLT_MAX);
    printf("Digitos de precision= %d bits\n",FLT_MANT_DIG);


    printf("\n=== DOBLE PRECISION (double) ===\n");
    printf("Epsilon (DBL_EPSILON)= %.20e\n",DBL_EPSILON);
    printf("Min positivo normalizado
    = %.20e\n", DBL_MIN);
    printf("Min positivo (incluyendo subnormales) = %.10e\n",
    DBL_TRUE_MIN);
    printf("Max valor representable
    = %.20e\n", DBL_MAX);
    printf("Digitos de precision= %d bits\n",
    DBL_MANT_DIG);
    return 0;
}