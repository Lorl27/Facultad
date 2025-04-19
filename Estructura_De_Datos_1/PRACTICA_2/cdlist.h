#ifndef __CDLIST_H__
#define __CDLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);

typedef int (*FuncionComparadora) (int dato1, int dato2);

typedef enum {
    CdLIST_RECORRIDO_HACIA_ADELANTE,
    CdLIST_RECORRIDO_HACIA_ATRAS
 } CDListOrdenDeRecorrido;

typedef struct _CDNodo {
  int dato;
  struct _CDNodo *sig;
  struct _CDNodo *ant;
} CDNodo;

typedef struct _cdlist{
  CDNodo *ultimo;
} CDlist;

/**
 * Devuelve una lista vacía.
 */
CDlist Cdlist_crear();

/**
 * Destruccion de la lista.
 */
void Cdlist_destruir(CDlist *lista);

/**
 * Determina si la lista es vacía.
 */
int Cdlist_vacia(CDlist lista);

/**
 * Agrega un elemento al final de la lista.
 */
CDlist Cdlist_agregar_final(CDlist *lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
CDlist Cdlist_agregar_inicio(CDlist *lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void Cdlist_recorrer(CDlist lista, FuncionVisitante visit);

void Cdlist_recorrer_elegir(CDlist lista,FuncionVisitante visit, CDListOrdenDeRecorrido orden);

//-------

/* Devuelve la longitud de la lista*/
//int Cdlist_longitud(CDlist lista);

/* Concatena l1 (modificandola) con l2.*/
//void Cdlist_concatenar(CDlist l1, CDlist l2);

/* Inserta un elemento en la pos deseada*/
//CDlist Cdlist_insertar(CDlist lista,int dato,int pos);

/* Elimina de la lista, el elemento en la pos indiciada*/
//CDlist Cdlist_eliminar(CDlist lista, int pos);

/* Elimina de la lista, el elemento indicado*/
//CDlist Cdlist_borrar_dato(CDlist lista,int dato);

/* Determina si un elemento esta en una lista dada,
* -1: Error
* 1: No está
* 0: Está
*/
//int Cdlist_contiene(CDlist lista, int dato);

/* Devuelve la posicion de la primera ocurrencia de un elemento si el mismo esta en
la lista dada, y -1 en caso que no est´e */
//int Cdlist_indice(CDlist lista, int elemento);

/* Devuelve una nueva lista con los elementos comunes (independientemente de
la posici´on) de dos listas dadas por par´ametro. Las listas originales no se modifican. */
//CDlist Cdlist_intersecar(CDlist lista1, CDlist lista2);

/* Devuelve una lista nueva con los elementos comunes de lista1 y lista2, según el fptr de comparación.*/
//CDlist Cdlist_intersecar_custom(CDlist lista1, CDlist lista2, FuncionComparadora comp);

/* Ordena una lista de acuerdo al criterio dado por una funci´on de comparaci´on
(que usa los mismos valores de retorno que strcmp()). 
>0  --> la primera cadena es menor que la 2da
0 ---> son iguales
<0 --> la primera cadena es mayor que la 2da
*/
//CDlist Cdlist_ordenar(CDlist lista, FuncionComparadora comp);

/* Obteniene el reverso de una lista.*/
//CDlist Cdlist_reverso(CDlist lista); 

/* Dadas dos listas, intercale sus elementos en la lista resultante.
Por ejemplo,dadas las listas [1, 2, 3, 4] y [5, 6],
debe obtener la lista [1, 5, 2, 6, 3, 4]. */
//CDlist Cdlist_intercalar(CDlist lista1, CDlist lista2);

/* Divide una lista a la mitad.
* En caso de longitud impar (2n + 1), la primer lista tendra longitud n + 1 y la segunda, n.
* Retorna un puntero al primer elemento de la segunda mitad, siempre que sea no vacıa. */
//CDlist Cdlist_partir(CDlist lista);


#endif /* __CDLIST_H__ */
