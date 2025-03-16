// 3. Arreglando programas

// Ejercicio 4. Cada uno de los siguientes fragmentos de programas tienen, al menos, un error
// y/o alguna construcción no recomendable. Identifíquelos y de alternativas para su re-escritura.

// 1. Alcance (scope) de variables:
#include <stdio.h>


void initialize(int a, int *b)
{
    if (a > 0)
    {
        *b = 1;
    }
    else
    {
        *b = 0;
    }
}
int main()
{
    int a = 1;
    int b;
    initialize(a,&b);
    printf(" %d %d \n ", a, b);
    return 0;
}