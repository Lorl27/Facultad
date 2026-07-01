#include "tablahash_diccionario.h"
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
        tabla->elementos[x].estado = VACIA;
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
    if(tabla->elementos[x].estado==OCUPADA) destroy(tabla->elementos[x].dato);
  }

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elementos);
  free(tabla);
  return;
}

void tablahash_insertar(TablaHash tabla, void *dato, FuncionDestructora destroy, FuncionCopiadora copy, FuncionComparadora comp){

  // Verificamos el factor de carga (numElems / casillas)
  // Usamos (float) para que la división no de cero al ser enteros
  float factor_carga = (float)(tabla->numElementos + 1) / tabla->capacidad;
    
  if (factor_carga > 0.7) tablahash_redimensionar(tabla);
  
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x = tabla->hash(dato) % tabla->capacidad;
  unsigned inicio = x; // Guardamos donde empezamos para detectar si dimos la vuelta completa

  do {
      // Encontramos un lugar disponible (nunca usado o donde hubo una baja)
      if (tabla->elementos[x].estado == VACIA || tabla->elementos[x].estado == ELIMINADA) {
          tabla->elementos[x].dato = copy(dato);
          tabla->elementos[x].estado = OCUPADA;
          tabla->numElementos++;
          return;
      } 
      // El casillero esta ocupado. ¿Es el mismo elemento que queremos insertar?
      else if (comp(tabla->elementos[x].dato, dato) == 0) {
          destroy(tabla->elementos[x].dato);
          tabla->elementos[x].dato = copy(dato);
          return;
      }
        
      // ¡Colision! Linear probing: avanzamos 1 paso circularmente
      x = (x + 1) % tabla->capacidad;
        
    }while(x != inicio);

}

void *tablahash_buscar(TablaHash tabla, void *dato,FuncionComparadora comp){

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x =tabla->hash(dato) % tabla->capacidad;
  unsigned inicio = x;

  // Seguimos buscando mientras NO encontremos una celda VACIA
  while(tabla->elementos[x].estado != VACIA){
      if(tabla->elementos[x].estado == OCUPADA && comp(tabla->elementos[x].dato, dato) == 0){
          return tabla->elementos[x].dato;
      }
      x = (x + 1) % tabla->capacidad;
      if(x == inicio) break; // Dimos toda la vuelta y no esta
  }

  return NULL;
}


void tablahash_eliminar(TablaHash tabla, void *dato,FuncionComparadora comp, FuncionDestructora destroy){

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned x = tabla->hash(dato) % tabla->capacidad;
  unsigned inicio = x;

  while(tabla->elementos[x].estado != VACIA){
      if(tabla->elementos[x].estado == OCUPADA && comp(tabla->elementos[x].dato, dato) == 0){
          destroy(tabla->elementos[x].dato);
          tabla->elementos[x].dato = NULL;
          tabla->elementos[x].estado = ELIMINADA; // Dejamos la lápida (tombstone)
          tabla->numElementos--;
          return;
      }
      x = (x + 1) % tabla->capacidad;
      if(x == inicio) break; // Dimos toda la vuelta
  }

}



void tablahash_redimensionar(TablaHash tabla) {
    // 1. Calculamos la nueva capacidad y pedimos memoria
    unsigned nueva_capacidad = tabla->capacidad * 2;
    CasillaHash *nuevos_elementos = malloc(sizeof(CasillaHash) * nueva_capacidad);
    
    if (nuevos_elementos == NULL) return; // Falla de memoria (buena práctica)

    // 2. Inicializamos el nuevo arreglo
    for (unsigned i = 0; i < nueva_capacidad; i++) {
        nuevos_elementos[i].dato = NULL;
         nuevos_elementos[i].estado = VACIA; 
    }

    // 3. Guardamos referencias al arreglo viejo
    CasillaHash *viejos_elementos = tabla->elementos;
    unsigned vieja_capacidad = tabla->capacidad;

    // 4. Conectamos el nuevo arreglo a la tabla y reiniciamos el contador
    tabla->elementos = nuevos_elementos;
    tabla->capacidad = nueva_capacidad;
    tabla->numElementos = 0; 

    // 5. TRASLADO FÍSICO (Rehashing)
    // Recorremos la tabla vieja y mudamos a los sobrevivientes
    for (unsigned i = 0; i < vieja_capacidad; i++) {
        
        // Si hay un dato real (y no está eliminado/vacío)
        if (viejos_elementos[i].dato != NULL) { 
            void *dato_a_mover = viejos_elementos[i].dato;
            
            // Recalculamos el índice usando el módulo de la NUEVA capacidad
            unsigned nuevo_indice = tabla->hash(dato_a_mover) % nueva_capacidad;
            
            // Resolvemos colisiones en la nueva tabla (Linear Probing)
            while (tabla->elementos[nuevo_indice].dato != NULL) {
                nuevo_indice = (nuevo_indice + 1) % nueva_capacidad;
            }
            
            // Mudamos el dato a su nueva casa y aumentamos el contador
            tabla->elementos[nuevo_indice].dato = dato_a_mover;
            tabla->elementos[nuevo_indice].estado = OCUPADA;
            
            tabla->numElementos++;
        }
    }

    // 6. Destruimos la estructura vieja, ¡pero NO los datos que estaban adentro!
    free(viejos_elementos);
}