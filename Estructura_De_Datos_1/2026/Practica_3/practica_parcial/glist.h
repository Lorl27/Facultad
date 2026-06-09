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

typedef GList SGList;

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

/* Inserta al inicio de la lista*/
GList insertar_inicio(GList lista, void * dato, FuncionCopia copy);

/*
* Dadas dos listas, intercala sus elementos en la lista resultante.
 Por ejemplo, dadas las listas [1, 2, 3, 4] y [5, 6],
 debe obtener la lista [1, 5, 2, 6, 3, 4].
*/
GList glist_intercalar(GList lista1, GList lista2,FuncionCopia copy);

/*
* Divide una lista a la mitad. 
En caso de longitud impar (2n+ 1), la primer lista
tendra longitud n+ 1 y la segunda n.
 Retorna un puntero al primer elemento de la segunda mitad,
siempre que sea no vacıa
*/
GList glist_partir(GList lista);



/*
* Devuelve una nueva lista con los elementos comunes (independientemente de
la posicion) de dos listas dadas por parametro.
 Las listas originales no se modifican.
*/
GList glist_intersecar(GList lista1, GList lista2,FuncionCopia copy);

/*
* * Devuelve una nueva lista con los elementos comunes , definidos por una funcion de comparacion , (independientemente de
la posicion) de dos listas dadas por parametro.
 Las listas originales no se modifican.
*/
GList glist_intersercar_custom(GList lista1, GList lista2,FuncionComparadora fun,FuncionCopia copy);

/*
* Devuelve la concatenaciòn de 2 listas, modificando la primera
*/
GList glist_concatenar(GList lista1, GList lista2);

/*
* Ordena una lista de acuerdo al criterio dado por una funcion de comparacion
(que usa los mismos valores de retorno que strcmp()) pasada por parametro
0: son iguales
<0: la primera cadena es menor
>0: la primera cadena es mayor
*/
GList glist_ordenar(GList lista,FuncionComparadora fun);

//------- ordenadas:
/* Inserta un nuevo dato en la lista ordenada. La funcion de comparacion es la que determina el criterio de
ordenacion*/
SGList sglist_insertar(SGList lista, void * dato, FuncionCopia copy, FuncionComparadora comp);

/* Busca un dato en la lista ordenada,
 retornando 1 si lo encuentra y 0 en caso contrario
  (aprovechar que la lista est´a ordenada para hacer esta busqueda mas eficiente).*/
int sglist_buscar(GList lista, void * dato, FuncionComparadora comp);

/* Construye una lista ordenada a partir de un arreglo de elementos y su longitud.*/
SGList sglist_arr(void ** array, int long_array, FuncionCopia copy, FuncionComparadora comp);


#endif /* __GLIST_H__ */
