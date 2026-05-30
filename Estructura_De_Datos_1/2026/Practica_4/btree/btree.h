#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante)(void * dato);
typedef void (*FuncionDestructora)(void * dato);
typedef void * (*FuncionCopia)(void * dato);
typedef void (*FuncionVisitanteExtra) (void * dato, void *extra);
/* Retorna 
x<0 si el primero es menor que el segundo,
x=0 si son iguales,
x>0 si el primero es mayor que el segundo.
  */
typedef int (*FuncionComparadora) (void *a , void * b);
//typedef void * (*FuncionSuma)(void *a, void *b);
typedef void * (*FuncionTransformadora)(void * dato);

typedef enum {
  BTREE_RECORRIDO_IN, //Subàrbol izquierdo - procesar la raìz - subàrbol derecho
  BTREE_RECORRIDO_PRE,//Procesar la raìz - subàrbol izquierdo - subàrbol derecho
  BTREE_RECORRIDO_POST//ubàrbol izquierdo - subàrbol derecho - procesar la raìz
} BTreeOrdenDeRecorrido;


typedef struct _BTNodo{
    void * dato;
    struct _BTNodo *izq;
    struct _BTNodo *der;
} BTNodo;

typedef BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo,FuncionDestructora destroy);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void * dato, BTree left, BTree right,FuncionCopia copy);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,FuncionVisitante visit);

/**
 * Recorrido iterativo del arbol de forma PREORDEN, utilizando la funcion pasada.
 */
void btree_recorrer_iterativo(BTree arbol,FuncionVisitante visit);

/*
Retorna el nro de nodos del àrbol
*/
int btree_nnodos(BTree arbol);

/*
Retorna 1 si el nro dado està en el arbol. 0 en caso contrario.
*/
int btree_buscar(BTree arbol, void * numero,FuncionComparadora fun);

/*
Retorna un nuevo àrbol que es una copia del àrbol dado
*/
BTree btree_copiar(BTree arbol,FuncionCopia copy);

/*
Retorna la altura del àrbol
*/
int btree_altura(BTree arbol);

/*
Retorna el nro de nodos que se encuentran a la profundidad dada
*/
int btree_nnodos_profundidad(BTree arbol,int profundidad);

/*
Retorna la profundidad del nodo que contiene el nùmero dado,
-1 si el nro no esta en el àrbol.
*/
int btree_profundidad(BTree arbol, void * numero,FuncionComparadora fun);

/*
* Retorna la suma total de los datos del àrbol.
 */
//void * btree_sumar(BTree arbol,FuncionSuma sum);


/**
 * Recorrido del arbol, utilizando la funcion pasada tanto para el nodo como para el dato extra
 */
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void *extra);

/*
* Bùsqueda por extensiòn - iterativa.
*/
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit);

/*
* Retorne la cantidad de nodos "hoja"
*/
int btree_contar_hojas(BTree arbol);

/*
* Determina si tienen exactamente la misma forma y los mismos datos.
 Retorna 1 si son iguales, 0 en caso contrario.
*/
int btree_son_iguales(BTree arbol1, BTree arbol2, FuncionComparadora cmp);

/*
* Cuenta cuántos nodos tienen exactamente un solo hijo
*/
int btree_contar_un_hijo(BTree arbol);

/*
* Un árbol binario se considera "Estrictamente Binario" (o lleno) si todos sus nodos cumplen una regla: o son hojas (0 hijos), o tienen exactamente 2 hijos. No se permiten nodos con un solo hijo.
Escribe una función que retorne 1 si el árbol es estricto, o 0 si tiene al menos un nodo que rompa la regla.
Ayuda: Un árbol vacío se considera estricto (retorna 1).
*/
int btree_es_estricto(BTree arbol);

/*
Un árbol se considera "degenerado" o "lista" si absolutamente todos sus nodos internos tienen exactamente 1 hijo (la excepción es la única hoja del final, que tiene 0).
Escribe una función que retorne 1 si el árbol tiene forma de lista, o 0 si en algún momento el camino se bifurca en 2 hijos.
Ayuda: Un árbol vacío o con un solo nodo se considera degenerado (retorna 1).
*/
int btree_es_lista(BTree arbol);

/*
* Devuelve el puntero al dato máximo almacenado
*/
void * btree_maximo(BTree arbol, FuncionComparadora cmp);

/*
* Recibe un árbol y devuelve un árbol nuevo (reservando memoria)
 que sea su reflejo o "espejo" (los hijos izquierdos pasan a ser derechos, y viceversa).
*/
BTree btree_espejo(BTree arbol, FuncionCopia copy);

/*
* Recorre todo el árbol y cuenta cuántas veces aparece un dato específico.
*/
int btree_contar_apariciones(BTree arbol, void * dato_buscado, FuncionComparadora comp);

/*
* Elimina todas las hojas de un árbol binario.
*/
BTree btree_podar_hojas(BTree arbol, FuncionDestructora destroy);

/*
* Retorna un árbol completamente nuevo donde a cada dato se le aplicó una transformación.
*/
BTree btree_mapear(BTree arbol, FuncionTransformadora transformar);
#endif /* __BTREE_H__ */
