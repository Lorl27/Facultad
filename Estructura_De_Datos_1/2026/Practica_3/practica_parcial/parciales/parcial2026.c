#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pila/pila.h"

//1)
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




//2)

struct _Pila {
    char **arr;
    int ultimo;
    int capacidad;
};

typedef struct _Pila *Pila;


// crea e inicializa una nueva pila vac´ıa con la capacidad dada.
Pila pila_crear(int);
// libera la memoria requerida para la pila.
void pila_destruir(Pila);
// retorna 1 si la pila esta vacıa y 0 en caso contrario.
int pila_es_vacia(Pila);
// retorna el tope de la pila (sin eliminar).
char *pila_tope(Pila);
// inserta una cadena en el tope de la pila.
// Redimensiona la pila al doble de su tamano en caso de ser necesario.
void pila_apilar(Pila, char*);
// elimina el elemento que se encuentra en el tope de la pila.
void pila_desapilar(Pila);
// imprime el contenido de la pila desde el elemento
// m´as antiguo hasta el m´as recientemente insertado
void pila_imprimir(Pila);

/*Implemente eliminar iguales adyacentes que recibe un arreglo de cadenas y 
la cantidad de cadenas en el arreglo e imprime en pantalla las palabras del arreglo 
excepto por pares de palabras iguales adyacentes.
Las palabras se muestran en el orden original del arreglo y no se modiﬁca el arreglo original.
Note que como producto de una eliminaci´on se pueden habilitar otras eliminaciones. Todas ellas se debenrealizar.

$ eliminar_iguales_adyacentes({"ana","ana","beto","beto","carla","denise","carla"}, 7)
carla
denise
carla
$ eliminar_iguales_adyacentes({"ana","beto","beto","ana"}, 4)

$ eliminar_iguales_adyacentes({"ana","ana","ana"}, 3)
ana

*/


void eliminar_iguales_adyacentes(char ** arr, int n){
    if(arr==NULL || n==0) return;

    Pila pila_unicos=pila_crear(n);

    for(int x=0;x<n;x++){
        if(pila_es_vacia(pila_unicos)|| strcmp(pila_tope(pila_unicos),arr[x])!=0) pila_apilar(pila_unicos,arr[x]);
        else pila_desapilar(pila_unicos);
    }

    pila_imprimir(pila_unicos);
    pila_destruir(pila_unicos);
}