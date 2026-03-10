#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);

typedef int (*FuncionComparadora) (int dato1, int dato2);

typedef struct _DNodo {  
  int dato;
  struct _DNodo *sig;   //puntero al siguiente NODO
  struct _DNodo *ant;   //puntero al anterior NODO
} DNodo;  //NULL ← [3] ↔ [5] ↔ [9] → NULL

typedef struct {
  DNodo *primero;  //puntero al primer nodo
  DNodo *ultimo;  //puntero al ultimo nodo!
} DList;


typedef enum {
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;


/**
 * 
 * [lista]
    primero ─┬─> [1] <─> [4] <─> [8] <──┐
             └─────────────────────────┘
                              ultimo ───┘


🧩 Insertamos otro al inicio (ej: 1):
Creamos [1]

Lo conectamos:
[1].sig = [4]
[4].ant = [1]

NULL ← [1] ↔ [4] ↔ [8] → NULL

[lista] → primero: [1]
          ultimo : [8]
 */

/**
 * Devuelve una lista vacía.
 */
DList Dlist_crear();

/**
 * Destruccion de la lista.
 */
void Dlist_destruir(DList lista);

/**
 * Determina si la lista es vacía.
 */
int Dlist_vacia(DList lista);

/**
 * Agrega un elemento al final de la lista.
 */
DList Dlist_agregar_final(DList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
DList Dlist_agregar_inicio(DList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void Dlist_recorrer(DList lista, FuncionVisitante visit);

//----

void Dlist_recorrer_elegir(DList lista,FuncionVisitante visit, DListOrdenDeRecorrido orden);

//-------

/* Devuelve la longitud de la lista*/
int Dlist_longitud(DList lista);

/* Concatena l1 (modificandola) con l2.*/
void Dlist_concatenar(DList *l1, DList *l2);

/* Inserta un elemento en la pos deseada*/
void Dlist_insertar(DList *lista,int dato,int pos);

/* Elimina de la lista, el elemento en la pos indiciada*/
DList Dlist_eliminar(DList lista, int pos);

/* Elimina de la lista, el elemento indicado*/
void Dlist_borrar_dato(DList *lista,int dato);

/* Determina si un elemento esta en una lista dada,
* -1: Error
* 1: No está
* 0: Está
*/
int Dlist_contiene(DList lista, int dato);

/* Devuelve la posicion de la primera ocurrencia de un elemento si el mismo esta en
la lista dada, y -1 en caso que no est´e */
int Dlist_indice(DList lista, int elemento);

/* Devuelve una nueva lista con los elementos comunes (independientemente de
la posici´on) de dos listas dadas por par´ametro. Las listas originales no se modifican. */
DList Dlist_intersecar(DList lista1, DList lista2);

/* Devuelve una lista nueva con los elementos comunes de lista1 y lista2, según el fptr de comparación.*/
DList Dlist_intersecar_custom(DList lista1, DList lista2, FuncionComparadora comp);

/* Ordena una lista de acuerdo al criterio dado por una funci´on de comparaci´on
(que usa los mismos valores de retorno que strcmp()). 
>0  --> la primera cadena es menor que la 2da
0 ---> son iguales
<0 --> la primera cadena es mayor que la 2da
*/
DList Dlist_ordenar(DList *lista, FuncionComparadora comp);

/* Obteniene el reverso de una lista.*/
DList Dlist_reverso(DList *lista); 

/* Dadas dos listas, intercale sus elementos en la lista resultante.
Por ejemplo,dadas las listas [1, 2, 3, 4] y [5, 6],
debe obtener la lista [1, 5, 2, 6, 3, 4]. */
DList Dlist_intercalar(DList lista1, DList lista2);

/* Divide una lista a la mitad.
* En caso de longitud impar (2n + 1), la primer lista tendra longitud n + 1 y la segunda, n.
* Retorna un puntero al primer elemento de la segunda mitad, siempre que sea no vacıa. */
DList Dlist_partir(DList *lista);


#endif /* __DLIST_H__ */
