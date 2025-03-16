// Ejercicio 6: Construir un programa que calcule y presente por pantalla el signo del zodiaco, a partir de la introducción por teclado del día y mes de nacimiento como números enteros:
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

void signo(int dia, int mes) {
    if ((mes == 1 && dia >= 21) || (mes == 2 && dia <= 19)) {
        printf("Tu signo zodiacal es Acuario.\n");
    } else if ((mes == 2 && dia >= 20) || (mes == 3 && dia <= 20)) {
        printf("Tu signo zodiacal es Piscis.\n");
    } else if ((mes == 3 && dia >= 21) || (mes == 4 && dia <= 19)) {
        printf("Tu signo zodiacal es Aries.\n");
    } else if ((mes == 4 && dia >= 20) || (mes == 5 && dia <= 20)) {
        printf("Tu signo zodiacal es Tauro.\n");
    } else if ((mes == 5 && dia >= 21) || (mes == 6 && dia <= 21)) {
        printf("Tu signo zodiacal es Géminis.\n");
    } else if ((mes == 6 && dia >= 22) || (mes == 7 && dia <= 21)) {
        printf("Tu signo zodiacal es Cáncer.\n");
    } else if ((mes == 7 && dia >= 22) || (mes == 8 && dia <= 21)) {
        printf("Tu signo zodiacal es Leo.\n");
    } else if ((mes == 8 && dia >= 22) || (mes == 9 && dia <= 22)) {
        printf("Tu signo zodiacal es Virgo.\n");
    } else if ((mes == 9 && dia >= 23) || (mes == 10 && dia <= 22)) {
        printf("Tu signo zodiacal es Libra.\n");
    } else if ((mes == 10 && dia >= 23) || (mes == 11 && dia <= 21)) {
        printf("Tu signo zodiacal es Escorpio.\n");
    } else if ((mes == 11 && dia >= 22) || (mes == 12 && dia <= 21)) {
        printf("Tu signo zodiacal es Sagitario.\n");
    } else if ((mes == 12 && dia >= 22) || (mes == 1 && dia <= 20)) {
        printf("Tu signo zodiacal es Capricornio.\n");
    } else {
        printf("Fecha inválida. ERROR.\n");
    }
}

int main() {
    int dia, mes;

    printf("Ingrese su día de nacimiento: \n");
    scanf("%d", &dia);

    printf("Ingrese su mes de nacimiento: \n");
    scanf("%d", &mes);

    signo(dia, mes);

    return 0;
}
