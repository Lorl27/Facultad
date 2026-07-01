#include "tablahash.h"
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
        tabla->elementos[x].dato = NULL;
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
    if(tabla->elementos[x].dato!=NULL) destroy(tabla->elementos[x].dato);
  }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elementos);
  free(tabla);
  return;
}

void tablahash_insertar(TablaHash tabla, void *dato, FuncionDestructora destroy, FuncionCopiadora copy, FuncionComparadora comp){

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x = tabla->hash(dato) % tabla->capacidad;

  // Insertar el dato si la casilla estaba libre.
  if (tabla->elementos[x].dato==NULL) {
    tabla->numElementos++;
    tabla->elementos[x].dato=copy(dato);
    return;
  }

  // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
  else if (comp(tabla->elementos[x].dato, dato)==0) {
    destroy(tabla->elementos[x].dato);
    tabla->elementos[x].dato=copy(dato);
    return;
  }
  // No hacer nada si hay colision.
  else {
    return;
  }

}

void *tablahash_buscar(TablaHash tabla, void *dato,FuncionComparadora comp){

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x =tabla->hash(dato) % tabla->capacidad;

  // la casilla estaba vacia.
  if(tabla->elementos[x].dato == NULL) return NULL;
  // Retornar el dato de la casilla si hay concidencia.
  else if(comp(tabla->elementos[x].dato,dato)==0)return tabla->elementos[x].dato;
  
  return NULL;
}


void tablahash_eliminar(TablaHash tabla, void *dato,FuncionComparadora comp, FuncionDestructora destroy){

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x = tabla->hash(dato) % tabla->capacidad;

  if(tabla->elementos[x].dato != NULL){
    // Vaciar la casilla si hay coincidencia.
    if(comp(tabla->elementos[x].dato,dato) == 0) {
      tabla->numElementos--;
      destroy(tabla->elementos[x].dato);
      tabla->elementos[x].dato = NULL;
      return;
    }
  }

}
