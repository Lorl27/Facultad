#ifndef __SGLIST_H__
#define __SGLIST_H__


typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

typedef GList SGList;

/* Retorna 
x<0 si el primero es menor que el segundo,
x=0 si son iguales,
x>0 si el primero es mayor que el segundo.
  */
typedef int (*FuncionComparadora)(void * a, void* b);

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

/* Rtorna una lista ordenada vacıa. */
SGList sglist_crear();

/* Destruye una lista ordenada.
*/
void sglist_destruir(SGList lista, FuncionDestructora destroy);

/*Determina si una lista ordenada es vacıa.*/
int sglist_vacia(SGList lista);

/* Aplica la funcion visitante a cada elemento de la lista ordenada.
*/
void sglist_recorrer(SGList lista, FuncionVisitante visit);

/* Inserta un nuevo dato en la lista ordenada. La funcion de comparacion es la que determina el criterio de
ordenacion*/
SGList sglist_insertar(SGList lista, void * dato, FuncionCopia copy, FuncionComparadora comp);

/* Busca un dato en la lista ordenada,
 retornando 1 si lo encuentra y 0 en caso contrario
  (aprovechar que la lista est´a ordenada para hacer esta busqueda mas eficiente).*/
int sglist_buscar(GList lista, void * dato, FuncionComparadora comp);

/* Construye una lista ordenada a partir de un arreglo de elementos y su longitud.*/
SGList sglist_arr(void ** array, int long_array, FuncionCopia copy, FuncionComparadora comp);


#endif