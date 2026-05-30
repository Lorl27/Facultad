#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Practica_2/glist/glist.h"

typedef struct {
    char * nombre;
    int edad;
} Persona;

typedef struct _BNodo{
    struct _BNodo *izq;
    struct _BNodo *der;
    Persona * persona;
} BNodo;

typedef BNodo * BTree;



typedef void (*FuncionVisitanteExtra)(void * data, void * acumulador);

void btree_recorrer_extra(BTree arbol, FuncionVisitanteExtra visit, void * dato){
    if(arbol==NULL) return;

    visit(arbol->persona,dato);
    btree_recorrer_extra(arbol->izq,visit,dato);
    btree_recorrer_extra(arbol->der,visit,dato);
}

void btree_filtrar(BTree arbol,GList * lista_resultado, FuncionVisitanteExtra condicion){
    if(arbol==NULL) return;

    btree_recorrer_extra(arbol,condicion,lista_resultado);
}

BTree crear_arbol(){
    return NULL;
}

BTree unir_arbol(BTree izq, BTree der, void * dato, FuncionCopia copy){
    BTree arbol_new=malloc(sizeof(struct _BNodo));
    if(arbol_new!=NULL){
        arbol_new->persona=copy(dato);
        arbol_new->der=der;
        arbol_new->izq=izq;

    }

    return arbol_new;
}


/*
void * copiar_personas(void * persona){
    Persona * persona_pasada= (Persona * )persona;
}
*/
Persona * copiar_personas(Persona * persona){
    Persona * person=malloc(sizeof(Persona));
    person->edad=persona->edad;
    person->nombre=malloc(strlen(persona->nombre)+1);
    strcpy(person->nombre,persona->nombre);
    return person;
}


void solo_mayores(Persona * persona, GList * lista){
    int edad = persona->edad;

    if(edad>18)*lista=glist_agregar_inicio(*lista,persona,copiar_personas);
}

int main(){
    GList lista_mayor_18=glist_crear();

    Persona persona1={"roberto",18};
    Persona persona2={"magnifica",19};
    Persona persona3={"azul",2};

    BTree arbol=crear_arbol();
    BTree nodo1=unir_arbol(NULL,NULL,&persona1,(FuncionCopia)copiar_personas);
    BTree nodo2=unir_arbol(NULL,NULL,&persona2,(FuncionCopia)copiar_personas);
    BTree nodo3=unir_arbol(nodo1,nodo2,&persona3,(FuncionCopia)copiar_personas);

    btree_filtrar(arbol,&lista_mayor_18,(FuncionVisitanteExtra)solo_mayores);

    return 0;
}
