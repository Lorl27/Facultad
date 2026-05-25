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

// Devuelve el "peso" del operador (jerarquía)
int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // Para los paréntesis
}


// Función auxiliar que extrae y opera
void resolver_tope(Pila pila_numeros, Pila pila_operadores) {
    // Sacamos el operador
    char op = *(char*)Top(pila_operadores);
    Pop(pila_operadores, destruir_dato);

    // Sacamos el de la DERECHA primero
    int der = *(int*)Top(pila_numeros);
    Pop(pila_numeros, destruir_dato);

    // Sacamos el de la IZQUIERDA segundo
    int izq = *(int*)Top(pila_numeros);
    Pop(pila_numeros, destruir_dato);

    // Hacemos la cuenta
    int resultado = aplicar_operacion(izq, der, op);

    // Apilamos el resultado
    Push(pila_numeros, &resultado, copiar_enteros);
}

//------------------

int eval(char expresion_arit[]){
    if(expresion_arit==NULL) return 0;

    Pila pila_numeros=pila_crear();
    Pila pila_operadores=pila_crear();

    for(int x=0;expresion_arit[x]!='\0';x++){
        char c =expresion_arit[x];

        // Omitimos espacios en blanco por si acaso
        if(c == ' ') continue;

        if(tiene_numeros(expresion_arit[x])){
            int numero= expresion_arit[x] - '0';
            pila_numeros=Push(pila_numeros,&numero,copiar_enteros);
        }

        else if (expresion_arit[x]=='('){
            pila_operadores=Push(pila_operadores,&expresion_arit[x],copiar_char);
        }

        
        else if (expresion_arit[x]==')'){
            // Resolvemos todo hasta chocar con el paréntesis abierto '('
            while(!isEmpty(pila_operadores) && *(char*)Top(pila_operadores) != '(') {
                resolver_tope(pila_numeros, pila_operadores);
            }
            // Sacamos el '(' de la pila de operadores
            if(!isEmpty(pila_operadores)) {
                pila_operadores=Pop(pila_operadores, destruir_dato);
            }
        }
        else { // Es un operador (+, -, *, /)
            // Mientras haya un operador en la pila con MAYOR O IGUAL jerarquía, lo resolvemos primero
            while(!isEmpty(pila_operadores) && precedencia(*(char*)Top(pila_operadores)) >= precedencia(c)){
                resolver_tope(pila_numeros, pila_operadores);
            }
            // Finalmente, apilamos el operador actual
            Push(pila_operadores, &c, copiar_char);
        }
    }

    // Al terminar de leer la palabra, resolvemos lo que haya quedado pendiente
    while(!isEmpty(pila_operadores)){
        resolver_tope(pila_numeros, pila_operadores);
    }

    int resultado=*(int*)Top(pila_numeros);
    pila_numeros=pila_destruir(pila_numeros,destruir_dato);
    pila_operadores=pila_destruir(pila_operadores,destruir_dato);

    return resultado;
}