
#include <stdio.h>
#include <stdlib.h>

//1)

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *a, void *b);

//a.

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;


typedef GNode * SOList;

//b.

SOList solist_add(SOList lista, void * dato, FuncionCopia copy, FuncionComparadora comp){

    GNode *nuevo = malloc(sizeof(GNode));
    nuevo->data = copy(dato);

    if (lista == NULL || comp(lista->data, dato) > 0) {
        nuevo->next = lista;
        return nuevo;
    }

    GNode *inicio = lista;
    GNode *actual = lista->next;

    while (actual != NULL && comp(actual->data, dato) <= 0) {
        inicio = actual;
        actual = actual->next;
    }

    nuevo->next = actual;
    inicio->next = nuevo;

    return lista;
}

//c.

void solist_destroy(SOList list, FuncionDestructora destroy) {
  if(list==NULL) return;

    GNode * nodo=list;
    GNode * tmp;

    while (nodo != NULL) {
        tmp=nodo;
        nodo = nodo->next;
        destroy(tmp->data);
        free(tmp);
    }
}

//d.

void solist_print(SOList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}



//e.

int  comparar_enteros(void *a, void * b){
    int a_e=*(int*)a;
    int b_e=*(int*)b;
    return a_e-b_e;
}

void * copiar_enteros(void * a){
    int * entero=malloc(sizeof(int));
    *entero=*(int*)a;
    return entero;
}

void imprimir_enteros(void * a){
    printf("%d",*(int*)a);
}

void destruir_enteros(void * a) {free(a);}

void print_ordered(int arr[], int n){
    SOList lista = NULL;

    for(int x=0;x<n;x++){
        lista=solist_add(lista,&arr[x],comparar_enteros,copiar_enteros);
    }

    solist_print(lista,imprimir_enteros);

    solist_destroy(lista,destruir_enteros);
}

//2)

//s.x=1 y a[0]=42

/* La razòn es que la estructura, al no pasarse mediante punteros solo se modifica localemnte, en cambio
un array tiene como especial que es un puntero a la primera posicion del mismo es decir ar[0] y por ello,
èste sì que se modifica. */