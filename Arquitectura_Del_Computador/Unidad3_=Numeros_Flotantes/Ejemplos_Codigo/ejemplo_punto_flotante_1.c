#include <stdio.h>
#include <float.h>

int main()
{
    float f=-3.14;
    float* p=&f;
    int a=*(int *)p;
    printf("%#x\n", a);
    printf("Signo: %#x\n", (a>>31)&1);
    printf("Mantisa: %#x\n", a&0x7fffff);
    printf("Exponente: %#x\n", (a>>23)&0xff);
    printf("-------------------------------------------------\n");
    printf("Rango float: [%e, %e]\n", FLT_MIN, FLT_MAX);
    printf("Precisión float (epsilon): %e\n", FLT_EPSILON);
    printf("Rango de exponentes: [%d, %d]\n", FLT_MIN_EXP, FLT_MAX_EXP);
    printf("-------------------------------------------------\n");
    printf("Rango double: [%e, %e]\n", DBL_MIN, DBL_MAX);
    printf("Precisión double (epsilon): %e\n", DBL_EPSILON);
    printf("Rango de exponentes: [%d, %d]\n", DBL_MIN_EXP, DBL_MAX_EXP);
    return 0;
}
