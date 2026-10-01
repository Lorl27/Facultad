#include <stdio.h>
#include <stdint.h>
#include <math.h>

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


/*
3) Convierta a double y float norma IEEE 754 el n ́umero: N = 6.225. Realice el c ́alculo
de manera expl ́ıcita y luego corrobore el resultado mediante un programa que aproveche las
herramientas provistas en el ejercicio anterior. Analizar en cada caso si se ha cometido error de
representaci ́on y en caso afirmativo la magnitud del mismo.
*/

int main(void){
    float num_f=6.225f;
    double num_d=6.225;
    double real=6.225;

    printf("=== SIMPLE PRECISION (Float: %f) ===\n", num_f);
    printf("Manual   -> Signo: %u | Exponente: %u | Fraccion: 0x%X\n", signo_float(num_f), exponente_float(num_f), significando_float(num_f));  
     printf("\n[ERROR DE REPRESENTACIÓN]\n");
    // Comparamos el float almacenado (casteado a double) con el valor ideal
    printf("Error Absoluto : %e\n", error_absoluto(real, (double)num_f));
    printf("Error Relativo : %e\n\n", error_relativo(real, (double)num_f));

     printf("=== DOBLE PRECISION (Double: %f) ===\n", num_d);
    printf("Manual   -> Signo: %u | Exponente: %u | Fraccion: 0x%llX\n", signo_double(num_d), exponente_double(num_d), (unsigned long long)significando_double(num_d));

    printf("\n[ERROR DE REPRESENTACIÓN]\n");
    printf("Error Absoluto : %e\n", error_absoluto(real, num_d));
    printf("Error Relativo : %e\n\n", error_relativo(real, num_d));

    return 0;
}

/* 
$6.225 genera una secuencia binaria infinita.
 Como la máquina se ve obligada a "cortar la cola" de esa secuencia por la falta de espacio físico, se pierde información irreversible.
  Además, como en ambos casos la regla que aplicó fue la de redondear hacia abajo (truncar por toparse con un 0),
   el número que queda almacenado es matemáticamente un poco menor que 6.225.
*/
