#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() {
  return NULL;
}

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
int glist_vacia(GList list) {
  return (list == NULL);
}

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
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

//-------------

GList glist_filtrar(GList lista, FuncionCopia c, Predicado p){
  if(glist_vacia(lista)) return NULL;

  GList listaf=glist_crear();
  
  for(GNode *nodo=lista;nodo!=NULL;nodo=nodo->next){
    if(p(nodo->data)){
      listaf=glist_agregar_inicio(listaf,nodo->data,c);
    }
  }

  return listaf;
}

//-------------

SGList sglist_crear(){
  return NULL;
}

void sglist_destruir(SGList lista, FuncionDestructora f){
  GNode *nodo;
  while(lista!=NULL){
    nodo=lista;
    lista=lista->next;
    f(nodo->data);
    free(nodo);
  }
  
}

int sglist_vacia(SGList lista){
  return lista==NULL;
}

void sglist_recorrer(GList lista, FuncionVisitante f){
  if(lista==NULL) return;

  f(lista->data);
  sglist_recorrer(lista->next,f);

}

SGList sglist_insertar(SGList lista, void * dato, FuncionCopia c, FuncionComparadora f){
   GNode *nodoNuevo=malloc(sizeof(GNode));
    nodoNuevo->data=c(dato);
    nodoNuevo->next=NULL;

  if(lista==NULL || f(dato,lista->data)<0) {
    nodoNuevo->next=lista;
    return nodoNuevo;
  }

  GNode *nodo=lista;
  for(;nodo->next!=NULL && f(dato,nodo->next->data)>=0;nodo=nodo->next);

    nodoNuevo->next=nodo->next;
    nodo->next=nodoNuevo;

  return lista;
}

int sglist_buscar(GList lista, void *dato, FuncionComparadora f){
  if(lista==NULL) return 0;

  for(GNode *nodo=lista;nodo!=NULL;nodo=nodo->next){
    if(f(dato,nodo->data)==0){
      return 1;
    }
  }

  return 0;
}

/** Más eficiente:
 * int sglist_buscar(GList lista, void *dato, FuncionComparadora f){
  for(GNode *nodo = lista; nodo != NULL; nodo = nodo->next){
    int cmp = f(dato, nodo->data);
    if(cmp == 0) return 1;
    if(cmp < 0) return 0; // Ya pasó el punto donde podría estar
  }
  return 0;
}

 */

SGList sglist_arr(void **array, int longitud, FuncionCopia c, FuncionComparadora f){
  assert(c != NULL && f != NULL);
  if(array==NULL || longitud<=0) return NULL;

  SGList lista=sglist_crear();
  for(int x=0;x<longitud;x++){
    lista=sglist_insertar(lista,array[x],c,f);
  }

  return lista;
}