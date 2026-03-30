#include "matriz.h"

//mxn bidimensional fila i , col j: M[i][j]

/*
** Implementacion utilizando un arreglo bidimensional (arreglo de punteros a arreglo)
*/

struct Matriz_ {
  double ** arreglo;
  size_t filas;
  size_t cols;

};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz * matriz = malloc(sizeof(Matriz));
  if(matriz==NULL) return NULL;

  // PASO 1: Crear el arreglo principal que guarda PUNTEROS (las filas)
  // Nota el sizeof(double*). Estamos pidiendo espacio para guardar flechas.
  matriz->arreglo=malloc(sizeof(double*) * numFilas);
  if(matriz->arreglo==NULL){
    free(matriz);
    return NULL;
  }

  // PASO 2: Crear los arreglos secundarios (las columnas) para cada fila
  for(size_t fila=0; fila<numFilas; fila++) {
      matriz->arreglo[fila] = malloc(sizeof(double) * numColumnas);
      if(matriz->arreglo[fila]==NULL){
          for (size_t j=0; j<fila;j++) {
            free(matriz->arreglo[j]);
          }
          free(matriz->arreglo);
          free(matriz);
          return NULL;
      }
  }

  matriz->filas=numFilas;
  matriz->cols=numColumnas;
  return matriz;

}

void matriz_destruir(Matriz* matriz) {
  if(matriz!=NULL){
    for(int x=0;x<matriz->filas;x++){
        free(matriz->arreglo[x]);
    }
    free(matriz->arreglo);
    free(matriz);
  }
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  if(matriz==NULL || fil>=matriz->filas || col>=matriz->cols) return -1;

  return matriz->arreglo[fil][col];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  if(matriz!=NULL && fil<matriz->filas && col<matriz->cols){
    matriz->arreglo[fil][col]=val;
  }
}

size_t matriz_num_filas(Matriz* matriz) {
  if(matriz==NULL) return -1;
  return matriz->filas;
}

size_t matriz_num_columnas(Matriz* matriz) {
    if(matriz==NULL) return -1;
    return matriz->cols;

}

void matriz_intercambiar_filas(Matriz * matriz, size_t fila_a, size_t fila_b){
  if(matriz!=NULL && fila_a<matriz->filas && fila_b<matriz->filas ){
    double *fila_quemada=matriz->arreglo[fila_a];
    matriz->arreglo[fila_a]=matriz->arreglo[fila_b];
    matriz->arreglo[fila_b]=fila_quemada;
  }
}



void matriz_insertar_fila(Matriz * matriz, size_t columna,int pos){
  // pos puede ser igual a filas si queremos insertar al final
    if(matriz != NULL && pos <= matriz->filas){
        
        // 1. Agrandamos el "lomo" (arreglo de punteros)
        double **nuevo_arreglo = realloc(matriz->arreglo, sizeof(double*) * (matriz->filas + 1));
        if (nuevo_arreglo == NULL) return; // Error de memoria
        matriz->arreglo = nuevo_arreglo;

        // 2. Empujamos los PUNTEROS hacia abajo (de atrás para adelante)
        for (size_t i = matriz->filas; i > pos; i--) {
            matriz->arreglo[i] = matriz->arreglo[i - 1];
        }

        // 3. Creamos la nueva fila en el hueco
        matriz->arreglo[pos] = malloc(sizeof(double) * matriz->cols);
        
        // 4. Actualizamos la cantidad de filas
        matriz->filas++;
    }
}

/*
VENTAJAS:

- Sintaxis natural: Permite escribir el código usando los dobles corchetes M[i][j], 
  lo que hace el código más fácil de leer.

- (Dato extra avanzado) Filas irregulares: Aunque no se usa en matrices matemáticas, 
  esta estructura permite tener filas de distintos tamaños (ej: la fila 0 tiene 3 
  elementos, la fila 1 tiene 10).

DESVENTAJAS:

- Acceso más lento: Sufre de doble salto de memoria y pérdida de eficiencia en el 
  caché (fragmentación en el Heap).

- Mayor consumo de memoria: Requiere reservar espacio extra para el arreglo de 
  punteros (el "lomo" de la matriz).

- Gestión compleja: Obliga a hacer un bucle for tanto para crearla como para 
  destruirla, aumentando el riesgo de fugas de memoria.
*/