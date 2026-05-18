#ifndef __CCDList_H__
#define __CCDList_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _DNodo{
    struct _DNodo * sig;
    struct _DNodo *ant;
    int dato;
} DNodo;

typedef struct _CDListEstructura{
    DNodo * primero; 
} CDListEstructura;

typedef CDListEstructura * CDList;

//NO, no es necesario mantener un puntero al ultimo elemento
// de la lista, ya que primero->ant seria el ultimo.

typedef enum CDListOrdenDeRecorrido {
CDList_RECORRIDO_HACIA_ADELANTE,
CDList_RECORRIDO_HACIA_ATRAS
} CDListOrdenDeRecorrido;

//funcion auxiliar:
typedef void (* funcionRecorredora) (int dato);

// OPeracicones bàssicas: crear - destrurir- insertar pos  - eliminar pos

/*
* Retorna una caja vacia
*/
CDList crear();

/*
*  Destruye una lista
*/
void destruir(CDList lista);

/*
Inserta el dato en la pos dada de la lista
*/
CDList insertar(CDList lista, int pos, int dato);

/*
Elimina la pos dada de la lista
*/
CDList eliminar(CDList lista, int pos);

// funciones màs avanzadas: es_vacia , longitud, recorrer (2 modos) , reverso

/*
1 : es vacia
0: NO es vacia.
*/
int es_vacia(CDList lista);

/*
Retorna la longitud de la lista
*/
int longitud(CDList lista);


/*
* Recorre la lista, con la funcion pasada por parametro.
Se puede elegir si se avanza o retrocede en el recorrido,
*/
void recorrer(CDList lista, CDListOrdenDeRecorrido orden, funcionRecorredora funcion);

/*
Retorna una lista al revès.
*/
CDList reverso(CDList lista);

#endif