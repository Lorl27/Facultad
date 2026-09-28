// 16) Implemente una funci´on printbin en lenguaje C:
// void printbin(long n);
// que tome un entero de 64 bits y lo imprima en binario. 
// Utilizar esta funci´on para mostrar
// en binario los n´umeros del Ejercicio 2.
// Ayuda: Se puede utilizar la funci´on realizada en el ejercicio anterior

#include <stdio.h>
#include <stdlib.h>

// Devuelve 0 si el b-ésimo bit es de n es 0,
//devuelve 1 si es 1.
int is_one(long n, int b){
    long mascara= n>>b;
    int resultado= mascara & 1;

    return resultado;
}

void printbin(long n){
    int b=63;
    whille(b>=0){
        print("%d",is_one(n,0));

        if(i%8==0) printf(" "); //cada 1 byte, separador.
        b--;
    }

    printf("\n");
}

int main(void){
    long a = 0b1001;
    long b = 0b10001110;

    printf("El bit a es: %d\t");printbin(a); 
    printf("El bit b es: %d\t");printbin(b);
    
    //---------- Valores del Ejercicio 2
    long a = 16;
    long b = -16;
    long c = 127;
    long d = -127;
    long e = -1;
    long f = 128;
    long g = -128;
    long h = -31;

    printf("a)  16: \t"); printbin(a);
    printf("b) -16: \t"); printbin(b);
    printf("c)  127:\t"); printbin(c);
    printf("d) -127:\t"); printbin(d);
    printf("e) -1:  \t"); printbin(e);
    printf("f)  128:\t"); printbin(f);
    printf("g) -128:\t"); printbin(g);
    printf("h) -31: \t"); printbin(h);

    return 0;
}