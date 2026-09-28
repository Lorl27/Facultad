// 9) Dados A = 200, B = 300, C = 500 y D = 400. Calcular S = A × B ×C ×
// D, interpretando los datos como enteros con signo. Imprimir el resultado por pantalla
// haciendo un programa en Lenguaje C con datos tipo int y analizar el resultado. Repetir
// para datos tipo long int.
// Ayuda: Para poder imprimir un long int se debe usar el modificador %ld.

#include <stdio.h>

int main(){
    signed int A=200, B=300, C=500, D=400;
    signed int S=A*B*C*D; //S= 200*300*500*400 = 12000000000 -> overflow
    printf("%d\n",S); //-1474836480
    signed long int L=A*B*C*D; //L= 200*300*500*400 = 12000000000
    printf("%ld\n",L); //12000000000
    return 0;
}