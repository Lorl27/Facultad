// Compilar con y sin la opción -no-pie. Ejecutar varias veces en ambos casos y comparar el valor de la direcciones. 

#include <stdio.h>

int global = 0x99;

int main()
{
    int local = 0x66;
    printf(" Variable local: 0x%x, Dirección variable local: %p \n", local, &local);
    printf(" Variable global: 0x%x, Dirección variable global: %p \n", global, &global);
    return 0;
}
