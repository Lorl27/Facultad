// Ejercicio 6. Construir un programa que calcule y presente por pantalla el signo del zodiaco
// a partir de la introducción por teclado del día y mes de nacimiento como números enteros
// Capricornio del 22 de diciembre al 20 de enero
// Acuario del 21 de enero al 19 de febrero
// Piscis del 20 de febrero al 20 de marzo
// Aries del 21 de marzo al 19 de abril
// Tauro del 20 de abril al 20 de mayo
// Géminis del 21 de mayo al 21 de junio
// Cáncer del 22 de junio al 21,de julio
// Leo del,22 de julio al 21 de agosto
// Virgo del,22 de agosto al 22 de septiembre
// Libra del 23 de septiembre al 22 de octubre
// Escorpio del 23 de octubre al 21 de noviembre
// Sagitario del 22 de noviembre al 21 de diciembre


#include <stdio.h>
#include <assert.h>
#include <string.h>

// Función para determinar el signo del zodiaco
const char* zodiaco(int dia, int mes) {
    if ((mes == 12 && dia >= 22) || (mes == 1 && dia <= 20)) {
        return "Capricornio";
    } else if ((mes == 1 && dia >= 21) || (mes == 2 && dia <= 19)) {
        return "Acuario";
    } else if ((mes == 2 && dia >= 20) || (mes == 3 && dia <= 20)) {
        return "Piscis";
    } else if ((mes == 3 && dia >= 21) || (mes == 4 && dia <= 19)) {
        return "Aries";
    } else if ((mes == 4 && dia >= 20) || (mes == 5 && dia <= 20)) {
        return "Tauro";
    } else if ((mes == 5 && dia >= 21) || (mes == 6 && dia <= 21)) {
        return "Géminis";
    } else if ((mes == 6 && dia >= 22) || (mes == 7 && dia <= 21)) {
        return "Cáncer";
    } else if ((mes == 7 && dia >= 22) || (mes == 8 && dia <= 21)) {
        return "Leo";
    } else if ((mes == 8 && dia >= 22) || (mes == 9 && dia <= 22)) {
        return "Virgo";
    } else if ((mes == 9 && dia >= 23) || (mes == 10 && dia <= 22)) {
        return "Libra";
    } else if ((mes == 10 && dia >= 23) || (mes == 11 && dia <= 21)) {
        return "Escorpio";
    } else if ((mes == 11 && dia >= 22) || (mes == 12 && dia <= 21)) {
        return "Sagitario";
    } else {
        return "Fecha inválida";
    }
}

void test_zodiaco() {
    // Pruebas para la función zodiaco
    assert(strcmp(zodiaco(15, 1), "Capricornio") == 0);
    assert(strcmp(zodiaco(25, 1), "Acuario") == 0);
    assert(strcmp(zodiaco(10, 2), "Acuario") == 0);
    assert(strcmp(zodiaco(25, 2), "Piscis") == 0);
    assert(strcmp(zodiaco(15, 3), "Piscis") == 0);
    assert(strcmp(zodiaco(25, 3), "Aries") == 0);
    assert(strcmp(zodiaco(15, 4), "Aries") == 0);
    assert(strcmp(zodiaco(25, 4), "Tauro") == 0);
    assert(strcmp(zodiaco(15, 5), "Tauro") == 0);
    assert(strcmp(zodiaco(25, 5), "Géminis") == 0);
    assert(strcmp(zodiaco(15, 6), "Géminis") == 0);
    assert(strcmp(zodiaco(25, 6), "Cáncer") == 0);
    assert(strcmp(zodiaco(15, 7), "Cáncer") == 0);
    assert(strcmp(zodiaco(25, 7), "Leo") == 0);
    assert(strcmp(zodiaco(15, 8), "Leo") == 0);
    assert(strcmp(zodiaco(25, 8), "Virgo") == 0);
    assert(strcmp(zodiaco(15, 9), "Virgo") == 0);
    assert(strcmp(zodiaco(25, 9), "Libra") == 0);
    assert(strcmp(zodiaco(15, 10), "Libra") == 0);
    assert(strcmp(zodiaco(25, 10), "Escorpio") == 0);
    assert(strcmp(zodiaco(15, 11), "Escorpio") == 0);
    assert(strcmp(zodiaco(25, 11), "Sagitario") == 0);
    assert(strcmp(zodiaco(15, 12), "Sagitario") == 0);
    //assert(strcmp(zodiaco(35, 12), "Fecha inválida") == 0);  // Fecha inválida
}

int main() {
    int dia, mes;
    printf("El siguiente programa le permitirá conocer su signo del zodiaco según su fecha de nacimiento.\n");
    printf("Ingrese el día de nacimiento: ");
    scanf("%d", &dia);
    printf("Ingrese el mes de nacimiento: ");
    scanf("%d", &mes);

    printf("Su signo del zodiaco es: %s\n", zodiaco(dia, mes));

    // Ejecución de pruebas
    test_zodiaco();

    printf("Todas las pruebas pasaron correctamente.\n");

    return 0;
}
