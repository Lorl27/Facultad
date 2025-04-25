#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitanteEntero) (int dato);

typedef int (*FuncionComparadoraEntero) (int dato1, int dato2);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitanteEntero visit);


//-------

/* Devuelve la longitud de la lista*/
int slist_longitud(SList lista);

/* Concatena l1 (modificandola) con l2.*/
void slist_concatenar(SList l1, SList l2);

/* Inserta un elemento en la pos deseada*/
SList slist_insertar(SList lista,int dato,int pos);

/* Elimina de la lista, el elemento en la pos indiciada*/
SList slist_eliminar(SList lista, int pos);

/* Elimina de la lista, el elemento indicado*/
SList slist_borrar_dato(SList lista,int dato);

/* Determina si un elemento esta en una lista dada,
* -1: Error
* 1: No está
* 0: Está
*/
int slist_contiene(SList lista, int dato);

/* Devuelve la posicion de la primera ocurrencia de un elemento si el mismo esta en
la lista dada, y -1 en caso que no est´e */
int slist_indice(SList lista, int elemento);

/* Devuelve una nueva lista con los elementos comunes (independientemente de
la posici´on) de dos listas dadas por par´ametro. Las listas originales no se modifican. */
SList slist_intersecar(SList lista1, SList lista2);

/* Devuelve una lista nueva con los elementos comunes de lista1 y lista2, según el fptr de comparación.*/
SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparadoraEntero comp);

/* Ordena una lista de acuerdo al criterio dado por una funci´on de comparaci´on
(que usa los mismos valores de retorno que strcmp()). 
>0  --> la primera cadena es menor que la 2da
0 ---> son iguales
<0 --> la primera cadena es mayor que la 2da
*/
SList slist_ordenar(SList lista, FuncionComparadoraEntero comp);

/* Obteniene el reverso de una lista.*/
SList slist_reverso(SList lista); 

/* Dadas dos listas, intercale sus elementos en la lista resultante.
Por ejemplo,dadas las listas [1, 2, 3, 4] y [5, 6],
debe obtener la lista [1, 5, 2, 6, 3, 4]. */
SList slist_intercalar(SList lista1, SList lista2);

/* Divide una lista a la mitad.
* En caso de longitud impar (2n + 1), la primer lista tendra longitud n + 1 y la segunda, n.
* Retorna un puntero al primer elemento de la segunda mitad, siempre que sea no vacıa. */
SList slist_partir(SList lista);


#endif /* __SLIST_H__ */
