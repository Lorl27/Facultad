#include <stdio.h>
#include <stdlib.h>

#define SOLO 1 //Se tiro solo la bola i
#define PAR 2 //Se tiraron juntos i-1 e i

/*
Estamos en el bolo i
Tenemos 2 opciones:
1. Tirar solo el bolo i: Ganamos A[i], el resto del puntaje es el mejor obtenido hasta i-1 
es decir: dp[i]=A[i] + dp[i-1] 

2. Tirar los bolos i-1 e i juntos Ganamos A[i-1]*A[1], el resto el puntaje es el mejoro btenido hasta i-2
Es decir: dp[i]=A[i-1]*A[1] + dp[i-2] 


Nos quedamos con la mejor de ambas.

Tiempo: O(n)
Memoria O(n)
*/
void bowling(int A[], int N) {
    int *dp = malloc(N * sizeof(int));
    int *decision = malloc(N * sizeof(int));

    // Caso base
    dp[0] = A[0]; //primer bola
    decision[0] = SOLO;

    //Segunda bola:
    if (N > 1) {
        int solo = A[0] + A[1];
        int par = A[0] * A[1];

        if (solo >= par) { //max=solo
            dp[1] = solo;
            decision[1] = SOLO;
        } else {
            dp[1] = par;
            decision[1] = PAR;
        }
    }

    // Programación dinámica
    for (int i = 2; i < N; i++) {
        int solo = dp[i - 1] + A[i];
        int par = dp[i - 2] + A[i - 1] * A[i];

        if (solo >= par) {
            dp[i] = solo;
            decision[i] = SOLO;
        } else {
            dp[i] = par;
            decision[i] = PAR;
        }
    }

    printf("Puntaje maximo: %d\n\n", dp[N - 1]);

    printf("Forma de obtenerlo:\n");

    // Reconstrucción
    int i = N - 1;

    while (i >= 0) {
        if (decision[i] == SOLO) {
            printf("Tirar bolo %d (valor %d)\n", i, A[i]);
            i--;
        } else {
            printf("Tirar bolos %d y %d (producto %d)\n",
                   i - 1, i, A[i - 1] * A[i]);
            i -= 2;
        }
    }

    free(dp);
    free(decision);
}
