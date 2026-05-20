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


GList glist_reverso(GList lista, FuncionCopia copy){
  if(!lista) return lista;

  GList reverso = glist_crear();
  GNode * tmp = lista;
  while(tmp!=NULL){
    reverso=glist_agregar_inicio(reverso,tmp->data,copy);
    tmp=tmp->next;
  }
  return reverso;

}


int longitud(GList lista){
  int contador=0;
  GNode *tmp=lista;
  while(tmp!=NULL){
    contador++;
    tmp=tmp->next;
  }
  return contador;
}

GList glist_eliminar_elemento_recursivamente(GList list, FuncionDestructora destroy, int index){
  if(index<0 || list==NULL) return list;

  if(index==0){
    GList resto = list->next;
    //list->next = NULL;
    //glist_destruir(list, destroy);
    destroy(list->data);
    free(list);
    return resto;
  }

  list->next=glist_eliminar_elemento_recursivamente(list->next,destroy,index-1);
  return list;

}


GList insertar(GList lista, void * dato, FuncionCopia copy,int pos){
  if(pos<0 || pos>longitud(lista) ) return lista;

  GNode * nuevo=malloc(sizeof(GNode));
  nuevo->data=copy(dato);

  if(pos==0){
    nuevo->next=lista;
    return nuevo;
  }

  if(!lista) return lista;

  GNode * inicio= lista;
  GNode * actual= lista->next;
  int contador=1;

  while(inicio!=NULL && contador<pos){
    inicio=actual;
    actual=actual->next;
    contador++;
  }

  if(inicio!=NULL && contador==pos){
    nuevo->next=actual;
    inicio->next=nuevo;
  }


  return lista;
}


GList eliminar(GList lista, FuncionDestructora destroy, int pos){
 if(pos<0 || pos>=longitud(lista) ) return lista;


  if(pos==0){
    GNode * tmp= lista;
    lista=lista->next;
    destroy(tmp->data);
    free(tmp);
    return lista;
  }

  if(!lista) return lista;

  GNode * inicio= lista;
  GNode * actual= lista->next;
  int contador=1;

  while(actual!=NULL && contador<pos){
    inicio=actual;
    actual=actual->next;
    contador++;
  }

  if(actual!=NULL && contador==pos){
    inicio->next=actual->next;
    destroy(actual->data);
    free(actual);
  }


  return lista;
}



int contiene(GList lista, void * dato_buscado , FuncionComparadora comp){
  for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
    if(comp(tmp->data,dato_buscado)==0) return 1;
  }
  return 0;
}


int buscar(GList lista, void * dato_buscado , FuncionComparadora comp){
  int x=0;
  for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
    if(comp(tmp->data,dato_buscado)==0) return x;
    x++;
  }
  return -1;
}

GList insertar_final(GList lista, void * dato,FuncionCopia copy){
  int longitud_lista=longitud(lista);
  return insertar(lista,dato,copy,longitud_lista);
}

GList map(GList lista, FUncionTransformadora fun, FuncionCopia copy){
  if(!lista) return lista;
  GList listaNueva= glist_crear();
  for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
    listaNueva=insertar_final(listaNueva,fun(tmp->data),copy);
  }
  /* otra forma es insertar al inicio y luego, usar reverso*/
  return listaNueva;
}




/** Las diferencias son:
 *  el dato definido en el Nodo es de tipo void * , al igual en las funciones auxiliares
 * Usamos la version 1 de lista simple
 * los datos pedidos en las funciones ej agregar inicio son tipo void *
 * para destruir, al ser generica debemos tener una forma especial la cual es pasada por parametros.
 * para agregar, debemos hacer una copia del dato ya que sino, al eliminar el dato tendriamos un puntero apuntando a la nada!
 * Necesitamos la copia fisica asi glist es dueña de su propia memoria ;)
 */


 