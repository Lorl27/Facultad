#include <stdio.h>
#include <stdint.h>
#include <ieee754.h> 
#include <math.h>


// ==========================================
//  CÁLCULO DE ERRORES (Absoluto y Relativo)
// ==========================================

double error_absoluto(double valor_real, double valor_maquina) {
    // Ea = |fl(x) - x|
    return fabs(valor_maquina - valor_real);
}

double error_relativo(double valor_real, double valor_maquina) {
    // Er = |fl(x) - x| / |x|
    if (valor_real == 0.0) return 0.0; // Evitar división por cero
    return fabs(valor_maquina - valor_real) / fabs(valor_real);
}

// --- (Simple Precisión) ---
uint32_t significando_float(float num)   { return (*(uint32_t *)&num) & 0x7FFFFF; }
uint32_t exponente_float(float num)      { return (*(uint32_t *)&num >> 23) & 0xFF; }
uint32_t signo_float(float num)          { return (*(uint32_t *)&num >> 31) & 1; }

// --- (Doble Precisión) ---
uint64_t significando_double(double num) { return (*(uint64_t *)&num) & 0xFFFFFFFFFFFFF; }
uint32_t exponente_double(double num)    { return (*(uint64_t *)&num >> 52) & 0x7FF; }
uint32_t signo_double(double num)        { return (*(uint64_t *)&num >> 63) & 1; }

// -- (Cuadruple Presición) --
#define EXTRAER_SIGNIFICANDO_CUADRUPLE(num) ( (*(unsigned __int128 *)&(num)) & (~((unsigned __int128)0) >> 16) )
#define EXTRAER_SIGNO_CUADRUPLE(num)        ( (int)(*(__uint128_t*)&(num) >> 127 & 1) )
#define EXTRAER_EXPONENTE_CUADRUPLE(num)    ( (int)(*(__uint128_t*)&(num) >> 112 & 0x7FFF) )

// =================

void imprimir_hexa_128(unsigned __int128 valor) {
    // Rompemos los 128 bits en dos mitades de 64 bits para que printf pueda leerlos
    uint64_t mitad_alta = (uint64_t)(valor >> 64);
    uint64_t mitad_baja = (uint64_t)valor;
    
    if (mitad_alta == 0) {
        // Si la mitad alta está vacía (ej. al imprimir solo el exponente)
        printf("0x%llX\n", (unsigned long long)mitad_baja);
    } else {
        // Imprimimos la alta, y la baja con ceros a la izquierda (%016llX) para no perder el formato
        printf("0x%llX%016llX\n", (unsigned long long)mitad_alta, (unsigned long long)mitad_baja);
    }
}

// =================

int main(void) {
   double real_teorico = 3.45;

    // --- BLOQUE 1: SIMPLE PRECISIÓN ---
    float num_f = 3.45f;
    union ieee754_float nativo_f;
    nativo_f.f = num_f;

    printf("=== SIMPLE PRECISION (Float: %f) ===\n", num_f);
    printf("Manual   -> Signo: %u | Exponente: %u | Fraccion: 0x%X\n", signo_float(num_f), exponente_float(num_f), significando_float(num_f));  
    printf("ieee754  -> Signo: %u | Exponente: %u | Fraccion: 0x%X\n\n", nativo_f.ieee.negative, nativo_f.ieee.exponent, nativo_f.ieee.mantissa);

    printf("\n[ERROR DE REPRESENTACIÓN]\n");
    // Comparamos el float almacenado (casteado a double) con el valor ideal
    printf("Error Absoluto : %e\n", error_absoluto(real_teorico, (double)num_f));
    printf("Error Relativo : %e\n\n", error_relativo(real_teorico, (double)num_f));

    // --- BLOQUE 2: DOBLE PRECISIÓN ---
    double num_d = 3.45;
    union ieee754_double nativo_d;
    nativo_d.d = num_d;

    printf("=== DOBLE PRECISION (Double: %f) ===\n", num_d);
    printf("Manual   -> Signo: %u | Exponente: %u | Fraccion: 0x%llX\n", signo_double(num_d), exponente_double(num_d), (unsigned long long)significando_double(num_d));
    printf("ieee754  -> Signo: %u | Exponente: %u | Fraccion: 0x%llX\n\n", nativo_d.ieee.negative, nativo_d.ieee.exponent,((unsigned long long)nativo_d.ieee.mantissa1 << 20) | (unsigned long long)nativo_d.ieee.mantissa0);

    printf("\n[ERROR DE REPRESENTACIÓN]\n");
    // Para ver el error microscópico en Double, comparamos contra una constante de mayor precisión
    double real_alta_precision = 3.45000000000000000001; 
    printf("Error Absoluto : %e\n", error_absoluto(real_alta_precision, num_d));
    printf("Error Relativo : %e\n\n", error_relativo(real_alta_precision, num_d));

    // --- BLOQUE 3: CUÁDRUPLE PRECISIÓN ---
    _Float128 num_q = 3.45Q;
    unsigned __int128 fraccion = EXTRAER_SIGNIFICANDO_CUADRUPLE(num_q);
    
    printf("=== CUÁDRUPLE PRECISIÓN (_Float128) ===\n");
    printf("Número original: 3.45\n");
    printf("Signo     : %d\n", EXTRAER_SIGNO_CUADRUPLE(num_q));
    printf("Exponente : %d\n", EXTRAER_EXPONENTE_CUADRUPLE(num_q));
    printf("Fracción  : ");
    imprimir_hexa_128(fraccion);

    // Al ser el límite estándar del compilador, no graficamos error porque 
    // no tenemos un tipo nativo más grande en C para usar de "real teórico".
    printf("\n");

    return 0;
}