#include <stdio.h>
#include <stdint.h>
// Definimos la estructura exacta de un float de 32 bits
seg´un IEEE 754
typedef union {
float f;
struct {
uint32_t mantisa : 23;
uint32_t exponente : 8;
uint32_t signo : 1;
} bits;
} IEEE754_Float;
int main() {
IEEE754_Float numero;
numero.f =-12.5f; // N´umero de prueba
printf("Signo: %u\n", numero.bits.signo); // 1 (
Negativo)
printf("Exponente (con sesgo): %u\n", numero.bits.
exponente); // 130
printf("Mantisa (en hex): 0x%X\n", numero.bits.
mantisa); // 0x480000
return 0;
}