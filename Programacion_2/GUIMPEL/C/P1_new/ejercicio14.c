// Ejercicio 14: Los pacientes con síntomas de una cierta enfermedad son ingresados en el hospital si tienen un valor superior a 0.6 en la medición de un determinado índice, y son operados si el valor es superior a 0.9.
// Escribir un programa en C que lea desde teclado el número de pacientes seguido de la edad y el índice de cada paciente, y calcule la edad media de los pacientes analizados así como la edad media de los ingresados y la edad media de los operados

#include <stdio.h>

void calcular_edades(int total_pacientes, float *edad_media_ingresados, float *edad_media_operados, float *edad_media_total) {
    int edad, pacientes_ingresados = 0, pacientes_operados = 0;
    float indice, suma_edad_total = 0, suma_edad_ingresados = 0, suma_edad_operados = 0;

    for (int i = 0; i < total_pacientes; i++) {
        printf("Ingrese la edad y el índice del paciente %d: ", i + 1);
        scanf("%d %f", &edad, &indice);

        suma_edad_total += edad;

        if (indice > 0.9) {
            suma_edad_operados += edad;
            pacientes_operados++;
        } else if (indice > 0.6) {
            suma_edad_ingresados += edad;
            pacientes_ingresados++;
        }
    }

    // Calcular los promedios
    *edad_media_total = total_pacientes > 0 ? suma_edad_total / total_pacientes : 0;
    *edad_media_ingresados = pacientes_ingresados > 0 ? suma_edad_ingresados / pacientes_ingresados : 0;
    *edad_media_operados = pacientes_operados > 0 ? suma_edad_operados / pacientes_operados : 0;
}


void imprimir_resultados(float edad_media_total, float edad_media_ingresados, float edad_media_operados) {
    printf("Edad media de todos los pacientes: %.2f\n", edad_media_total);
    printf("Edad media de los ingresados: %.2f\n", edad_media_ingresados);
    printf("Edad media de los operados: %.2f\n", edad_media_operados);
}


int main() {
    int total_pacientes;
    float edad_media_total, edad_media_ingresados, edad_media_operados;

    printf("Ingrese el número total de pacientes: ");
    scanf("%d", &total_pacientes);

    calcular_edades(total_pacientes, &edad_media_ingresados, &edad_media_operados, &edad_media_total);

    imprimir_resultados(edad_media_total, edad_media_ingresados, edad_media_operados);

    return 0;
}
