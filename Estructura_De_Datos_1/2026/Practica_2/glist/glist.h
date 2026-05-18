#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *a, void *b);
typedef void * (*FUncionTransformadora)(void *a);

typedef int (*Predicado) (void *dato); //0: false - 1:true

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/* Dado una lista, retorna una copia de la misma segùn el predicado pasado*/
GList glist_filtrar(GList lista, FuncionCopia c, Predicado p);

/**
 * Dada una lista, devuelve una nueva lista con los mismos elementos pero en
 * orden inverso.
 */
GList glist_reverso(GList list, FuncionCopia copy);

/**
 * Elimina el elemento en la posición `index` de la lista `list` de forma
 * recursiva.
 *
 * Si `index` es menor a 0 o mayor o igual al número de elementos de la lista,
 * no se realiza ninguna eliminación.
 */
GList glist_eliminar_elemento_recursivamente(GList list, FuncionDestructora destroy, int index);

/*
Inserta un nodo en la pos elegida
*/
GList insertar(GList lista, void * dato, FuncionCopia copy,int pos);

/*
Devuelve la longitud de la lista
*/
int longitud(GList lista);

/* Elimina el nodo en la pos elegida
*/
GList eliminar(GList lista, FuncionDestructora destroy, int pos);


/*
Dada una lista, un void *dato_buscado y una FuncionComparadora, devolver 1 si el elemento está en la lista o 0 si no está.
*/
int contiene(GList lista, void * dato_buscado , FuncionComparadora comp);
/*
Dada una lista, un void *dato_buscado y una FuncionComparadora, devolver el indice  si el elemento está en la lista o -1 si no está.
*/

int buscar(GList lista, void * dato_buscado , FuncionComparadora comp);

/*
Toma una lista y una función transformadora, devolviendo una lista nueva con los datos transformados.
*/
GList map(GList lista, FUncionTransformadora fun, FuncionCopia copy);

/* Inserta al final de la lista*/
GList insertar_final(GList lista, void * dato, FuncionCopia copy);


#endif /* __GLIST_H__ */
