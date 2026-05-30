#ifndef __BSTREE_H__
#define __BSTREE_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void * a, void * b);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void * dato);


typedef enum {
  BTREE_RECORRIDO_IN,  /** Inorden */
  BTREE_RECORRIDO_PRE, /** Preorden */
  BTREE_RECORRIDO_POST /** Postorden */
} BSTreeRecorrido;


/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */
struct _BST_Nodo {
  void *dato;
  struct _BST_Nodo *izq;
  struct _BST_Nodo *der;
};

typedef struct _BST_Nodo *BSTree;

/**
 * Retorna un arbol de busqueda binaria vacio.
 */
BSTree bstee_crear();


/*
* Retorna si un arbol es vacio o no
*/
BSTree bstree_empty(BSTree arbol);

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree arbol, FuncionDestructora destroy);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree arbol, void * elemento, FuncionComparadora comp);

/**
 * Inserta un dato no repetido en el arbol, 
 * manteniendo la propiedad del arbol de busqueda binaria.
 */
BSTree bstree_insertar(BSTree arbol, void * elemento, FuncionCopiadora copy, FuncionComparadora comp);

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree arbol, BSTreeRecorrido orden, FuncionVisitanteExtra fun,void *extra);


/* 
Busca el elemento en el arbol y retorna el nodo en el que esta, sino existe: retorna NULL
*/
BSTree btree_search(BSTree arbol, void * elemento, FuncionComparadora comp);


/*
*Se realiza una bùsqueda del elemento x  a eliminar.
Si existe:...
1- si x es una hoja: se elimina inmediatamente
2- si x tiene un solo hijo: se cambia la referencia del padre de x, para que apunte al hijo de x
3- si x tiene 2 hijos: tenemos que analizar què dato debe ir en el lugar de x.
que bien puede ser el mìnimo nodo del subàrbol de recho de x, ò, el màximo nodo del subàrbol izquierdo de x.
*/
BSTree bstree_eliminar(BSTree arbol, void *dato,FuncionComparadora comp, FuncionDestructora fun);


/*
Busca el k-èsima elemento menor del àrbol
Base 1, el k=1 menor es el primero. No es como indice.
*/
void * bstree_k_esimo_menor(BSTree arbol, int k);

/*
Retorna el nro de nodos del àrbol
*/
int bstree_nnodos(BSTree arbol);

/* 
Retorna 1 si el arbol es ABB y, 0 si no
*/
int bstree_validar(BSTree arbol,FuncionComparadora comp);


/*
* Imprime el rango [min,max] de los datos del arbol pasado
*/
void bstree_imprimir_rango(BSTree arbol, void * min, void * max, FuncionComparadora comp, FuncionVisitante imprimir);

/*
* Busca el padre en comùn entre 2 datos que estan en el àrbol
*/
void * bstree_ancentro_comun(BSTree arbol, void * dato1, void* dato2, FuncionComparadora comp);

/*
* Escribir una función que busque un dato objetivo.

Si el objetivo está en el árbol, retorna ese mismo dato.

Si el objetivo NO está, debe retornar el menor de los mayores (es decir, el dato que le sigue inmediatamente hacia arriba).

Si no hay ninguno mayor, retorna NULL.
*/
void * bstree_techo(BSTree arbol, void * objetivo, FuncionComparadora comp);

/*
Retorna el valor minimo iterativamente
*/
void * bstree_minimo_iterativo(BSTree arbol);

/*
Cuenta cuántos datos en el ABB son estrictamente mayores a un limite dado.
*/
int bstree_contar_mayores(BSTree arbol, void * limite, FuncionComparadora comp);


/*
*Escribe una función que reciba un ABB de origen y
 retorne un nuevo ABB  insertando únicamente los datos que cumplan con una condición dada
*/
BSTree bstree_clonar_si(BSTree origen, Predicado cumple_condicion, FuncionCopiadora copy, FuncionComparadora comp);

/*
* Escribe una función que reciba un ABB y una lista de datos (un arreglo genérico de void *). 
La función debe retornar 1 si esos datos forman un camino descendente válido desde la raíz, o 0 en caso contrario.
*/
int bstree_validar_camino(BSTree arbol, void ** camino, int longitud_camino, FuncionComparadora comp);

#endif 