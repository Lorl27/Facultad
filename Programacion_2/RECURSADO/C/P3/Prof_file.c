#include <stdio.h>

struct estudiante{
    char nombre[50];
    int legajo;
    float nota;
};

typedef struct estudiante Estudiante;

int main(void){

    struct estudiante alumno1;
    Estudiante alumno2;
    
    printf("\n Ingrese siguientes datos del Estudiante 1:\n");

    printf("\n Nombre : ");
    gets(alumno1.nombre);

    printf("\n Legajo: ");
    scanf("%d", &alumno1.legajo);

    printf("\n Nota: ");
    scanf("%f", &alumno1.nota);

    /* Vaciar el buffer de entrada */
    while(getchar()!= '\n');	

    printf("\n Ingrese siguientes datos del Estudiante 2:\n");

    printf("\n Nombre : ");
    gets(alumno2.nombre);

    printf("\n Legajo: ");
    scanf("%d", &alumno2.legajo);

    printf("\n Nota: ");
    scanf("%f", &alumno2.nota);


    printf("\nLa información ingresada es:\n");

    printf("\nNombre: %s", alumno1.nombre);
    printf("\nLegajo: %d", alumno1.legajo);
    printf("\nNota: %.1f\n", alumno1.nota);

    printf("\nLa información ingresada es:\n");

    printf("\nNombre: %s", alumno2.nombre);
    printf("\nLegajo: %d", alumno2.legajo);
    printf("\nNota: %.1f\n", alumno2.nota);
    return 0;
}