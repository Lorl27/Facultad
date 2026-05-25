#include <stdio.h>
#include <stdlib.h>
#include "../Practica_3/Pila/pila.h"

void * copiar_char(void * caracter){
    char * copia=malloc(sizeof(char));
    *copia=*(char *)caracter;
    return copia;
}

void * copiar_enteros(void * caracter){
    char * copia=malloc(sizeof(int));
    *copia=*(int *)caracter;
    return copia;
}

void destruir_dato(void * dato){
    free(dato);
}

//---------------

int tiene_numeros(char caracter) {
    return caracter >= '0' && caracter <= '9';
}

// Ejecuta la cuenta y devuelve el resultado
int aplicar_operacion(int izq, int der, char op) {
    if (op == '+') return izq + der;
    if (op == '-') return izq - der;
    if (op == '*') return izq * der;
    if (op == '/') return izq / der;
    return 0;
}

// Función auxiliar que extrae y opera
void resolver_tope(Pila pila_numeros, char operador) {

    // Sacamos el de la DERECHA primero
    int der = *(int*)Top(pila_numeros);
    Pop(pila_numeros, destruir_dato);

    // Sacamos el de la IZQUIERDA segundo
    int izq = *(int*)Top(pila_numeros);
    Pop(pila_numeros, destruir_dato);

    // Hacemos la cuenta
    int resultado = aplicar_operacion(izq, der, operador);

    // Apilamos el resultado
    Push(pila_numeros, &resultado, copiar_enteros);
}

//------------------

int eval_posorder(char expresion_arit[]){
    if(expresion_arit==NULL) return 0;

    Pila pila_numeros=pila_crear();

    for(int x=0;expresion_arit[x]!='\0';x++){
        char c =expresion_arit[x];

        // Omitimos espacios en blanco por si acaso
        if(c == ' ') continue;

        if(tiene_numeros(expresion_arit[x])){
            int numero= expresion_arit[x] - '0';
            pila_numeros=Push(pila_numeros,&numero,copiar_enteros);
        }

        resolver_tope(pila_numeros, c);
    }
    


    int resultado=*(int*)Top(pila_numeros);
    pila_numeros=pila_destruir(pila_numeros,destruir_dato);

    return resultado;
}