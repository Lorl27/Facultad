// Ejercicio 5. Leer la nota de un alumno (entera) y mostrar un mensaje diciendo si sacó insifuciente (2 a 5)
//, aprobado (6), bueno (7), muy bueno (8), distinguido (9), sobresaliente (10). Se
// debe mostrar un mensaje si la nota es incorrecta. Este programa debe hacerse de dos maneras
// diferentes con: if secuenciales y, con if-else anidados.

#include <stdio.h>
#include <assert.h>

void evaluacion_notas_SECUENCIAL(int nota){
    if (nota >= 2 && nota <= 5){
        printf("insuficiente");
    }
    if (nota==6){
        printf("Aprobado");
    }
    if (nota==7){
        printf("Bueno");
    }
    if (nota==8){
        printf("Muy bueno");
    }
    if (nota==9){
        printf("Distinguido");
    }
    if (nota==10){
        printf("Sobresaliente");
    }
    if(nota<2 || nota>10){printf("NOTA NO VÁLIDA. RANGO ENTRE [2-10]");}
}

void evaluacion_notas_ANIDADOS(int nota){
    if (nota >= 2 && nota <= 10) {
        if (nota <= 5) {
            printf("insuficiente\n");
        } else if (nota == 6) {
            printf("Aprobado\n");
        } else if (nota == 7) {
            printf("Bueno\n");
        } else if (nota == 8) {
            printf("Muy bueno\n");
        } else if (nota == 9) {
            printf("Distinguido\n");
        } else if (nota == 10) {
            printf("Sobresaliente\n");
        }
    } else {
        printf("NOTA NO VÁLIDA. RANGO ENTRE [2-10]\n");
    }
}

int main(){
    int nota;
    printf("El siguiente programa le permitirá conocer el estado del alumno según su nota: \n");
    printf("Ingrese la nota del alumno");
    scanf("%d",&nota);
    printf("su condición es: ");
    evaluacion_notas_ANIDADOS(nota);
    printf("su condición es: ");
    evaluacion_notas_SECUENCIAL(nota);
    return 0;
}

