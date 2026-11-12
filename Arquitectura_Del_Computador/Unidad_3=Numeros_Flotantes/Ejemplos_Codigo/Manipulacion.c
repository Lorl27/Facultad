#include <stdio.h>
#include <stdint.h>
int main() {
float f =-12.5f;
// Forzamos al compilador a leer los bits del float
como un entero
uint32_t bits = *(uint32_t*)&f;
uint32_t signo = (bits >> 31) & 1;
uint32_t exponente = (bits >> 23) & 0xFF;
uint32_t mantisa = bits & 0x7FFFFF;
printf("Representaci´on hexadecimal completa: 0x%08X\
n", bits);
return 0;
}