#ifndef __CSLIST_ALTERNATIVA_H__
#define __CSLIST_ALTERNATIVA_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);


typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef struct _CSList {
  SNodo *primero;
  SNodo *ultimo;
} CSListEstructura; 

// Redefinimos SList para que sea un PUNTERO a la caja administradora
typedef CSListEstructura *CSList;


/**
 * Devuelve una lista vacía.
 */
CSList cslist_crear();

/**
 * Destruccion de la lista.
 */
void cslist_destruir(CSList lista);

/**
 * Determina si la lista es vacía.
 */
int cslist_vacia(CSList lista);
/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void cslist_recorrer(CSList lista, FuncionVisitante visit);

/*
* Devuelve la longitud de una lista
*/
int cslist_longitud(CSList lista);
/*
* Inserta un dato en una lista y en una pos arbitraria
*/
CSList cslist_insertar(CSList lista,int dato, int pos);

/*
* Borra de una lista un dato en una pos arbitraria
*/
CSList cslist_eliminar(CSList lista, int pos);
/*
* Obtiene el reverso de una lista
*/
CSList cslist_reverso(CSList lista);
#endif 