#ifndef __DLIST_H__ 
#define __DLIST_H__

#include <stdio.h>
#include <stdlib.h>


//Estructuras
typedef struct _DNodo{
    struct _DNodo * sig;
    int dato;
    struct _DNodo *ant;
} DNodo;


typedef struct _DListEstructura{
    DNodo *primero; 
    DNodo *ultimo;
} DListEstructura;

typedef DListEstructura * DList;

typedef enum {
DLIST_RECORRIDO_HACIA_ADELANTE,
DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

//funcion auxiliar:
typedef void (* funcionRecorredora) (int dato);

// OPeracicones bàssicas: crear - destrurir- insertar pos  - eliminar pos

/*
* Retorna una caja vacia
*/
DList crear();

/*
*  Destruye una lista
*/
void destruir(DList lista);

/*
Inserta el dato en la pos dada de la lista
*/
DList insertar(DList lista, int pos, int dato);

/*
Elimina la pos dada de la lista
*/
DList eliminar(DList lista, int pos);

// funciones màs avanzadas: es_vacia , longitud, recorrer (2 modos) , reverso

/*
1 : es vacia
0: NO es vacia.
*/
int es_vacia(DList lista);

/*
Retorna la longitud de la lista
*/
int longitud(DList lista);


/*
* Recorre la lista, con la funcion pasada por parametro.
Se puede elegir si se avanza o retrocede en el recorrido,
*/
void recorrer(DList lista, DListOrdenDeRecorrido orden, funcionRecorredora funcion);

/*
Retorna una lista al revès.
*/
DList reverso(DList lista);

#endif