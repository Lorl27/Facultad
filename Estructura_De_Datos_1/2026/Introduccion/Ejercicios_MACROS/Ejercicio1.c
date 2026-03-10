#include <stdio.h>

#define YES 1
#define NO 0

// #line 3000
#define TRUE 999 //para testeo

#if defined(TRUE)
#undef TRUE //ELimina la definiciòn anterior
#define TRUE 1
#endif

#ifdef TRUE
#undef TRUE
#define TRUE 1
#endif

#if TRUE != 0
    #define FALSE 0
#else
    #define FALSE 1
#endif


#define SQUARE_VOLUMEN(x) ((x)*(x)*(x))  //IMPORTANTE los parèntesis!
#define MACRO_MALA(x) (x * x * x)  //Si lo hubieramos dejado asi...

#line 3000 //para testeo la ponemos abajo.


int main() {
    printf("=== Prueba de Constantes ===\n");
    printf("YES: %d\n", YES);
    printf("NO: %d\n", NO);
    printf("TRUE (redefinido a 1): %d\n", TRUE);
    printf("FALSE (calculado por el preprocesador): %d\n", FALSE);
    
    printf("\n=== Prueba de Volumen ===\n");
    int lado = 5;
    printf("Volumen de un cubo de lado %d: %d\n", lado, SQUARE_VOLUMEN(lado));
    
    printf("Volumen enviando una expresion (2+3) con la macro CORRECTA: %d\n", SQUARE_VOLUMEN(2+3));
    printf("Volumen enviando una expresion (2+3) con la macro MALA: %d\n", MACRO_MALA(2+3));

    printf("\n=== Prueba de Numeracion de Lineas ===\n");
    printf("Esta impresion dice estar en la linea numero: %d\n", __LINE__);

    return 0;
}