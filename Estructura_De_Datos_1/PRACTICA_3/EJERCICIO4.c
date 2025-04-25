// 4. Implemente colas generales utilizando listas enlazadas generales.
// a) Piense qu´e tipo de lista ser´a necesaria (simple, doble, circular, con un puntero al ´ultimo nodo, u otra)
// para implementar colas de manera eficiente. En caso de no tener implementada la lista elegida de
// manera general, provea una implementaci´on de la misma, junto con su respectivo archivo cabecera

//* Como una cola solo va a vanzando hacia delante, nos conviene una lista simple con 2 punteros (al inicio y al final). La haremos general, aprovechando la ya dada .h y .c de la P2.

// b) Defina las siguientes operaciones b´asicas para colas. Nuevamente, procure manipular la lista
// ´unicamente a trav´es de las funciones declaradas en su interfaz.

#include "cola.h"

#include <stdio.h>
#include <stdlib.h>

// i. cola crear.
Cola *cola_crear(){
    Cola *c=malloc(sizeof(Cola));
    c->primero=NULL;
    c->ultimo=NULL;

    return c;
}

// ii. cola destruir.
void cola_destruir(Cola *cola, FuncionDestructoraCola destroy){
    if(cola==NULL) return;

    GNode *actual=cola->primero;

    while(actual!=NULL){
        GNode *sig=actual->next;
        destroy(actual->data);
        free(actual);
        actual=sig;
    }

    free(cola);
}

// iii. cola es vacia.
int cola_empty(Cola *cola){
    return cola->primero==NULL;
}

// iv. cola inicio (que retorna el elemento que se encuentre en el inicio de la cola, sin eliminarlo).
void *cola_inicio(Cola *cola){
    if(cola_empty(cola)) return NULL;

    return cola->primero->data;
}

// v. cola encolar.
void cola_encolar(Cola *cola,void *elemento, FuncionCopiaCola copy){
    

    GNode *nodo=malloc(sizeof(GNode));
    nodo->data=copy(elemento);
    nodo->next=NULL;

    if(cola_empty(cola)){
        cola->primero=nodo;
    }else{
        cola->ultimo->next=nodo;}

    cola->ultimo=nodo;
}

// vi. cola desencolar.
void cola_desencolar(Cola *cola,FuncionDestructoraCola destroy){
    if(cola_empty(cola)) return;

    GNode *inicio=cola->primero;
    cola->primero=inicio->next;
    
    destroy(inicio->data);
    free(inicio);


    if(cola->primero==NULL) cola->ultimo==NULL;
    
}

// vii. cola imprimir.
void cola_imprimir(Cola *cola, void (*mostrar)(void *)){
    if(cola_empty(cola)) return;

    GNode *actual=cola->primero;

    while(actual!=NULL){
        mostrar(actual->data);
        actual=actual->next;
    }
}


// Función para copiar enteros
void *copia_entero(void *dato) {
    int *nuevo = malloc(sizeof(int));
    *nuevo = *(int *)dato;
    return nuevo;
}

// Función para destruir enteros
void destruir_entero(void *dato) {
    free(dato);
}

// Función para imprimir enteros
void mostrar_entero(void *dato) {
    printf("%d\t", *(int *)dato);
}

int main() {
    Cola *miCola = cola_crear();

    int a = 10, b = 20, c = 30;

    printf("Encolando elementos...\n");
    cola_encolar(miCola, &a, copia_entero);
    cola_encolar(miCola, &b, copia_entero);
    cola_encolar(miCola, &c, copia_entero);

    printf("\nElemento al frente de la cola: ");
    int *inicio = (int *)cola_inicio(miCola);
    if (inicio) printf("%d\n", *inicio);
    else printf("Cola vacía\n");

    printf("\nContenido de la cola:\n");
    cola_imprimir(miCola, mostrar_entero);

    printf("\nDesencolando un elemento...\n");
    cola_desencolar(miCola, destruir_entero);

    printf("\nContenido de la cola tras desencolar:\n");
    cola_imprimir(miCola, mostrar_entero);

    printf("\nDestruyendo la cola...\n");
    cola_destruir(miCola, destruir_entero);

    return 0;
}