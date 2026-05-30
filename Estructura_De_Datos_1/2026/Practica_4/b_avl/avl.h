#ifndef __AVL_H__
#define __AVL_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void * dato_a, void * dato_b);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);
typedef int (*FuncionDistancia)(void * dato1, void * dato2);
typedef enum {
  AVL_RECORRIDO_IN,  /** Inorden */
  AVL_RECORRIDO_PRE, /** Preorden */
  AVL_RECORRIDO_POST /** Postorden */
} AVLRecorrido;

/**
 * Estructura del nodo del arbol AVL.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * un puntero al nodo raiz del subarbol derecho (der), y
 * un entero para representar la altura del arbol (altura)
 */
typedef struct _AVL_Nodo {
  void* dato;
  struct _AVL_Nodo * izq; 
  struct _AVL_Nodo* der;
  int altura;
} AVL_Nodo;


typedef AVL_Nodo * AVL;

/**
 * Retorna un arbol AVL vacio
 */
AVL avl_crear();

/* 
Retorna si esta vacio el arbol
*/
int avl_empty(AVL arbol);

/**
 * Destruye el arbol y sus datos.
 */
void avl_destruir(AVL arbol, FuncionDestructora destroy);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario
 */
int avl_buscar(AVL arbol, void * dato, FuncionComparadora comp);

/* retorna la altura del arbol, si esta vacio: -1*/
int avl_altura_arbol(AVL arbol);

/* Retorna la altura maxima altura de los hijos */
int avl_altura_max_hijos(AVL arbol);

/* Retorna el factor balance de un nodo */
int avl_factor_balance(AVL arbol);

/* Rotacion a la izquierda del arbol*/
AVL avl_rotacion_izquierda(AVL arbol);

/* Rotacion a la derecha del arbol*/
AVL avl_rotacion_derecha(AVL arbol);


/* Reestablece la propiedad de AVL,
aplicando automatimante rotaciones simples o dobles 
segùn el factor de balance */
AVL avl_rebalancear(AVL arbol);

/**
 * Inserta un dato no repetido en el arbol, 
 * manteniendo la propiedad de los arboles AVL.
 */
AVL avl_insertar(AVL arbol, void * dato, FuncionCopiadora copy, FuncionComparadora comp);

/* Valida que sea un ABB
- 1: lo es
- 0 : no lo es
*/
int avl_validar_que_es_abb(AVL arbol, FuncionComparadora comp);

/* Valida que la altura y el factor balance sean correctos
-1: lo es
- 0 : no lo es
*/
int avl_validar_altura_y_balance(AVL arbol);

/**
 * Retorna 1 si el arbol cumple la propiedad de los arboles AVL,
 *  y 0 en caso contrario.
 */
int avl_validar(AVL arbol, FuncionComparadora comp);

/**
 * Recorrido DSF del arbol
 */
void avl_recorrer(AVL arbol, AVLRecorrido orden, FuncionVisitanteExtra visit, void * extra);


/* elimina un dato del arbol, si es que este esta 
el resultado es un avl valido.
*/
AVL eliminar_elemento(AVL arbol, void * elemento, FuncionComparadora comp, FuncionDestructora destroy);

/*
determina si Un árbol está "perfectamente lleno".
Es decir, si absolutamente todos sus nodos tienen un Factor de Balance exactamente igual a 0.
*/
int avl_es_perfecto(AVL arbol);

/*
elimina las hojas y rebalancea si es necesario.
*/
AVL avl_podar_hojas(AVL arbol, FuncionDestructora destroy);

/*
Te dan un dato objetivo que no está en el árbol. 
Tu misión es encontrar el dato del árbol que tenga la menor "distancia" al objetivo. 
Para esto te dan una FuncionDistancia que retorna la diferencia absoluta entre dos datos.
*/
void * avl_mas_cercano(AVL arbol, void * objetivo, FuncionComparadora comp, FuncionDistancia dist);

/*
Calcule cuántos nodos en total se visitaron para encontrar un elemento en el árbol.
 Si el elemento no existe, debe retornar la cantidad de nodos que se visitaron hasta darse cuenta de que no estaba 
(es decir, hasta chocar con NULL).
*/
int avl_costo_busqueda(AVL arbol, void * elemento, FuncionComparadora comp);

#endif /* __AVL_H__*/