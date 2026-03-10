#include "glist.h"
#include <stdio.h>



typedef GList Pila;

// i. Pila pila crear(int): crea e inicializa una nueva pila vac´ıa con la capacidad dada.
Pila pila_crear();

// ii. void pila destruir(Pila): libera la memoria requerida para la pila.
void pila_destruir(Pila pila, FuncionDestructora destroy);

// iii. int pila es vacia(Pila): retorna 1 si la pila est´a vac´ıa, y 0 en caso contrario.
int pila_es_vacia(Pila pila);

// iv. int pila tope(Pila): retorna el elemento que se encuentre en el tope de la pila, pero sin
// eliminarlo.
int pila_tope(Pila pila);

// v. void pila apilar(Pila, int): inserta un elemento en el tope de la pila, en caso que la pila
// se encuentre llena, deber´a aumentar al doble la capacidad del arreglo.
// Ayuda: puede llamar a la funci´on arreglo enteros ajustar.

GList sglist_agregar_final(GList list, void *data, FuncionCopia copy);

void pila_apilar(Pila *pila, void *elemento,FuncionCopia c);

// vi. void pila desapilar(Pila): elimina el elemento que se encuentra en el tope de la pila.
void pila_desapilar(Pila *pila, FuncionDestructora destroy);

// vii. void pila imprimir(Pila): imprime en orden los elementos de la pila.
void pila_imprimir(Pila pila);

