/*


Para mover N discos de A a C:
1. Movemos los N-1 superiores A->B
2. Mover el disco + grande A->C
3. Movelos los N-1 B->C

Tiempop: O(2^n)
Memoria: O(n)
*/

void hanoi(int n, char origen, char auxiliar, char destino) {

    if (n == 1) {
        printf("Mover disco 1 de %c a %c\n", origen, destino);
        return;
    }

    hanoi(n - 1, origen, destino, auxiliar);

    printf("Mover disco %d de %c a %c\n", n, origen, destino);

    hanoi(n - 1, auxiliar, origen, destino);
}