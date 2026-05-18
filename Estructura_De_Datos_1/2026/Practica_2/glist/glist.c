#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  if (newNode == NULL) return NULL; 
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}


GList glist_filtrar(GList lista, FuncionCopia c, Predicado p){
  GList nueva = glist_crear();
  for(GNode *node = lista; node != NULL; node = node->next){
    if(p(node->data)){
      nueva=glist_agregar_inicio(nueva,node->data,c);
    }
  }
  return nueva;
}


/** Las diferencias son:
 *  el dato definido en el Nodo es de tipo void * , al igual en las funciones auxiliares
 * Usamos la version 1 de lista simple
 * los datos pedidos en las funciones ej agregar inicio son tipo void *
 * para destruir, al ser generica debemos tener una forma especial la cual es pasada por parametros.
 * para agregar, debemos hacer una copia del dato ya que sino, al eliminar el dato tendriamos un puntero apuntando a la nada!
 * Necesitamos la copia fisica asi glist es dueña de su propia memoria ;)
 */


 