#include <stdio.h>
#include <stdlib.h>
#include "../Practica_3/Pila/pila.h"

// Idea: Usar pila para almacenar la expresion entera, por cada nodo guardamos un parentèsis,
// Luego, contamos y realizamos Pop() 
//  Si los contadores son iguales -> està bien formada.
// Si no lo son -> no lo esta.

void * copiar_char(void * caracter){
    char * copia=malloc(sizeof(char));
    *copia=*(char *)caracter;
    return copia;
}

void destruir_char(char * c){
    free(c);
}

int bien_parentizada(char expresion[]){
    if(expresion==NULL) return 0;

    Pila pila= pila_crear();
    for(int x=0;expresion[x]!='\0';x++){
        if(expresion[x] == '(') pila=Push(pila,&expresion[x],copiar_char);
        if(expresion[x] == ')') {
            if(isEmpty(pila)) return 0; //no tiene su par.
            pila=Pop(pila,(FuncionDestructora)destruir_char);
        }
    }

    if(!isEmpty(pila)){ //cada parentesis deberia tener su par!
        pila=pila_destruir(pila,(FuncionDestructora)destruir_char);
        return 0;
    }

    pila=pila_destruir(pila,(FuncionDestructora)destruir_char);

    return 1; 
}



int bien_parentizada_contador(char expresion[]){

    if(expresion==NULL) return 0;

    int x=0;

    int parentesis_total=0;

    while(expresion[x]!='\0'){
        if(expresion[x]=='(') parentesis_total++;
        if(expresion[x]==')') parentesis_total--;
        if(parentesis_total < 0) return 0; //se rompe el orden. )(
        x++;
    }

    return parentesis_total==0;

}

//============================

int main() {
    char * pruebas[] = {
        "(a+b)",        // bien
        "((a+b)*c)",    // bien
        "(a+b))",       // mal
        "((a+b)",       // mal
        "a+b",          // bien (sin paréntesis)
        ")(a+b)",       // mal
        NULL
    };

    printf("=== Prueba con pila ===\n");
    for (int i = 0; pruebas[i] != NULL; i++) {
        printf("Expresion: %s -> %s\n",
               pruebas[i],
               bien_parentizada(pruebas[i]) ? "Bien parentizada" : "Mal parentizada");
    }

    printf("\n=== Prueba con contador ===\n");
    for (int i = 0; pruebas[i] != NULL; i++) {
        printf("Expresion: %s -> %s\n",
               pruebas[i],
               bien_parentizada_contador(pruebas[i]) ? "Bien parentizada" : "Mal parentizada");
    }

    return 0;
}