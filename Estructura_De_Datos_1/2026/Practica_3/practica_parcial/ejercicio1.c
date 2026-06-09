#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pila/pila.h"

typedef struct _GNodo{
    void * dato;
    struct _GNodo * sig;
} GNodo;

typedef GNodo * GList;


typedef void (*FuncionVisitante) (int dato);
typedef int (*FuncionComparadora) (int dato1,int dato2);
typedef void (*FuncionDestructora)(void * dato);
typedef void * (*FuncionCopia)(void * dato);


GList glist_insertar_ordenado(GList lista, void * dato, FuncionCopia copy, FuncionComparadora comp){
    GNodo * nodo = malloc(sizeof(struct _GNodo));
    nodo->dato=copy(dato);
    nodo->sig=NULL;

    //si es null ò si es menor al primer elemento
    if(lista==NULL || comp(lista->dato, dato)>0){
        nodo->sig=lista;
        return nodo;
    }

    GNodo * tmp = lista;
    //miramos siempre el siguiente
    while(tmp->sig!=NULL && comp(tmp->sig->dato, dato) <= 0){
        tmp=tmp->sig;
    }

    //encontramos uno donde es menor, hay que intercambiar.
    nodo->sig=tmp->sig;
    tmp->sig=nodo;

    return lista;
}


typedef struct {
    char * nombre;
    int edad;
} Persona;

int persona_comparar_edad(void * a, void * b){
    Persona * persona_a=(Persona *)a;
    Persona * persona_b=(Persona *)b;

    int edad_a=persona_a->edad;
    int edad_b=persona_b->edad;

    if(edad_a>edad_b) return 1;
    if(edad_b>edad_a) return -1;
    return 0;
}

void * copiar_persona(void * a){
    Persona * persona_a = (Persona *)a;
    Persona * persona_copia=malloc(sizeof(Persona));
    persona_copia->edad=persona_a->edad;
    persona_copia->nombre=malloc(strlen(persona_a->nombre)+1);
    strcpy(persona_copia->nombre,persona_a->nombre);
    return persona_copia;
}

int main(void){
    Persona  dummy={"roberto",49};
    GList lista_pasada=NULL;
    lista_pasada=glist_insertar_ordenado(lista_pasada,&dummy,copiar_persona,persona_comparar_edad);
    return 0;
}

void * copiar_palabras(void * palabra){
    char * palabra_copia = malloc(sizeof(char)*strlen(*(char*)palabra));
    strcpy(palabra_copia,*(char*)palabra);
    return palabra_copia;
}

void destruir_palabras(void * palabra){
    free(palabra);
}

void no_destruir(void * a){
    //...
}

void pila_imprimir(void * palabra){
    printf("%s",palabra);
}

void igualar_adyacentes(char ** palabras, int n){
    if(n==0||palabras==NULL) return;

    Pila pila=pila_crear();
    pila=Push(pila,palabras[1],copiar_palabras);

    for(int x=0 ; x<n;x++){

        if(!isEmpty(pila)&& strcmp(Top(pila),palabras[x])==0){
                pila=Pop(pila,destruir_palabras);
            }
            else{
                pila=Push(pila,palabras[x],copiar_palabras);
            }

        }

    pila_recorrer(pila,pila_imprimir);
    pila=pila_destruir(pila,destruir_palabras);
}
