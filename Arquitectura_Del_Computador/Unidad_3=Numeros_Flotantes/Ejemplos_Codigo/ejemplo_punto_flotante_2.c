#include <stdio.h>
#include <math.h>
int main() {
    float f = 0.0f;
    double d = 0.0;

    // Sumamos 0.1 cien veces
    for (int i = 0; i < 100; i++) {
        f += 0.1f;
        d += 0.1;
    }

    printf("Resultado con float : %.20f\n", f);
    printf("Resultado con double: %.20lf\n", d);

    // Comprobamos si llegan exactamente a 10.0
    if (f == 10.0f)
        printf("float == 10.0\n");
    else
        printf("float != 10.0\n");

    if (d == 10.0)
        printf("double == 10.0\n");
    else
        printf("double != 10.0\n");
        
    // Calcular errores
    double valor_real = 10.0;  // El valor exacto esperado
    
    double error_abs_f = fabs((double)f - valor_real);
    double error_rel_f = error_abs_f / valor_real;

    double error_abs_d = fabs(d - valor_real);
    double error_rel_d = error_abs_d / valor_real;

    // Mostrar resultados
    printf("float  = %.20f\n", f);
    printf("Error absoluto float = %.20e\n", error_abs_f);
    printf("Error relativo float = %.20e\n\n", error_rel_f);

    printf("double = %.20lf\n", d);
    printf("Error absoluto double = %.20e\n", error_abs_d);
    printf("Error relativo double = %.20e\n", error_rel_d);

    return 0;
}

