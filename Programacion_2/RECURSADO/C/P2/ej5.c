// Ejercicio 5. ¿Qué hace el siguiente programa?

#include <stdio.h>
int main() {
int x, y;
printf ("Ingrese dos enteros dentro del rango [1,20]:\n");
scanf(" %d %d", &x, &y);
if (x >=1 && y>=1 && x<=20 && y<=20) {
for (int i=1; i<=y; i++) {
for (int j=1; j<=x; j++) {
printf ("@");
}
printf ("\n");
}
} else {
printf("Los enteros no se encuentran en el rango pedido");
}
return 0;
}


//Lo que hace el siguentre programa es :
// - Le pide al usuario que ingrese 2 numeros en cierto rango, y luego verifica que cumplen el rango
// - En caso de que estén en el rango pedido, imprimirá a*b veces "@" (2  bucles for), separandos en cada iteración mayor por una línea nueva
// -- Es decir, a indica la cantidad de columnas y b, la cantidad de filas.
// - En caso de que no estén en el rango, muestra un mensaje de error.