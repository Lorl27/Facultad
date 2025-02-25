#include <stdio.h>
#include <ctype.h>

#define TAM 6

int solucion1() {
    char str[] = "bucle";
    char palabra_incompleta[TAM];
    char caracteres[] = "TsRqP";
    for(int i = 0; i < TAM-1; i++) {
        palabra_incompleta[i] = str[i];
        palabra_incompleta[i+1] = '\0';
        printf("%s %d %c\n", palabra_incompleta, 5-i, caracteres[i]);
    }
}

int solucion2() {
    char str[] = "bucle";
    
    char c = 'T';
    for(int i = 0; i < TAM-1; i++) {
        str[TAM-1] = str[i+1];
        str[i+1] = '\0';
        printf("%s %d %c\n", str, 5-i, i % 2 == 0 ? c : tolower(c));
        str[i+1] = str[TAM-1];
        c--;
    }
}

int solucion3() {
    char str[] = "bucle";

    for(int i = 0; i < TAM-1; i++) {
        str[TAM-1] = str[i+1];
        str[i+1] = '\0';
        printf("%s %d %c\n", str, 5-i, (i%2 == 0 ? 'T' : 't') - i);
        str[i+1] = str[TAM-1];
    }
}

int main() {
    solucion1();
    printf("\n");
    solucion2();
    printf("\n");
    solucion3();
}


// 24-oct , ej7,p2.