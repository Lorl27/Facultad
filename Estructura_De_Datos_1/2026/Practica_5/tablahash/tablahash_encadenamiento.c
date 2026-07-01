#include "tablahash_encadenamiento.h"
#include <stdlib.h>


TablaHash tablahash_crear(unsigned capacidad,FuncionHash hash){

  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  if(tabla!=NULL){
    tabla->numElementos = 0;
    tabla->capacidad = capacidad;
    tabla->hash = hash;

    tabla->elementos = malloc(sizeof(CasillaHash) * capacidad);
    if(tabla->elementos!=NULL){
      // Inicializamos las casillas con datos nulos.
      for (unsigned x=0;x<capacidad;++x) {
        tabla->elementos[x].cabeza = NULL;
      }
    }
    
  }

  return tabla;
}

int tablahash_nelementos(TablaHash tabla){
  return tabla->numElementos; 
}

int tablahash_capacidad(TablaHash tabla){
  return tabla->capacidad; 
}

void tablahash_destruir(TablaHash tabla,FuncionDestructora destroy){

  // Destruir cada uno de los datos.
  for(unsigned x=0;x<tabla->capacidad;++x){
    NodoHash *actual = tabla->elementos[x].cabeza;
    // Vaciamos la lista simplemente enlazada
    while(actual != NULL){
        NodoHash *tmp = actual;
        actual = actual->sig;
        destroy(tmp->dato);
        free(tmp);
    }
  }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elementos);
  free(tabla);
  return;
}

void tablahash_insertar(TablaHash tabla, void *dato, FuncionDestructora destroy, FuncionCopiadora copy, FuncionComparadora comp){

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x = tabla->hash(dato) % tabla->capacidad;
  NodoHash *actual = tabla->elementos[x].cabeza;

  // Buscamos si el dato ya existe en la lista para actualizarlo
  while(actual != NULL){
    if(comp(actual->dato, dato)==0){
        destroy(actual->dato);       // Liberamos el viejo
        actual->dato = copy(dato);   // Guardamos el nuevo
        return;
      }
      actual = actual->sig;
  }

  //Si hay colisión (o está vacía), insertamos un nuevo nodo al inicio
  NodoHash *nuevo = malloc(sizeof(NodoHash));
  if(nuevo==NULL) return; 

  nuevo->dato = copy(dato);
  nuevo->sig = tabla->elementos[x].cabeza;
    
  tabla->elementos[x].cabeza = nuevo;
  tabla->numElementos++;

}

void *tablahash_buscar(TablaHash tabla, void *dato,FuncionComparadora comp){

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x =tabla->hash(dato) % tabla->capacidad;
  NodoHash *actual = tabla->elementos[x].cabeza;

  while(actual != NULL){
    if(comp(actual->dato, dato) == 0) return actual->dato;
    actual = actual->sig;
  }

  return NULL;
}


void tablahash_eliminar(TablaHash tabla, void *dato,FuncionComparadora comp, FuncionDestructora destroy){

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x = tabla->hash(dato) % tabla->capacidad;
  NodoHash *actual = tabla->elementos[x].cabeza;
  NodoHash *prev = NULL;

  while(actual != NULL){
    if(comp(actual->dato, dato) == 0){
      if(prev == NULL) tabla->elementos[x].cabeza = actual->sig;
      else prev->sig = actual->sig;
          
      destroy(actual->dato);
      free(actual);
      tabla->numElementos--;
      return;
    }
    prev = actual;
    actual = actual->sig;
  }

}
