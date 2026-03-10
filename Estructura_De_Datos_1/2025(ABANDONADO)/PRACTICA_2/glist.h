#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef int (*Predicado) (void *dato);

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

//--------

/* Dada una lista general, retorne una nueva lista con los elementos que cumplen con el predicado.
Predicado retorna 1 cuando el dato cumple con el predicado y, 0 en caso contrario.*/
GList glist_filtrar(GList lista, FuncionCopia c, Predicado p);

//--------------------

typedef GList SGList;
typedef int (*FuncionComparadora)(void *, void *);

//Retorna una lista ordenada vacıa.
SGList sglist_crear();

//Destruye una lista ordenada.
void sglist_destruir(SGList lista, FuncionDestructora f);

//Determina si una lista ordenada es vacıa.
int sglist_vacia(SGList lista);

//Aplica la funci´on visitante a cada elemento de la lista ordenada.
void sglist_recorrer(GList lista, FuncionVisitante f);

/* Inserta un nuevo dato en la lista ordenada.
La funci´on de comparacion, retorna un entero negativo si el primer argumento es menor que el segundo, 0 si son iguales,
y un entero positivo en caso contrario. */
SGList sglist_insertar(SGList lista, void * dato, FuncionCopia c, FuncionComparadora f);

/*Busca un dato en la lista ordenada, 
retornando 1 si lo encuentra y,
0 en caso contrario (aprovechar que la lista est´a ordenada para hacer esta b´usqueda m´as eficiente). */
int sglist_buscar(GList lista, void *dato, FuncionComparadora f);

//Construye una lista ordenada a partir de un arreglo de elementos y su longitud.
SGList sglist_arr(void **array, int longitud, FuncionCopia c, FuncionComparadora f);

#endif /* __GLIST_H__ */
