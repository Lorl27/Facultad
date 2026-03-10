#include "matriz.h"
#include <stdio.h>

/*
** Implmentacion utilizando un unico arreglo unidimensional
*/

struct Matriz_ {

  float *array;
  int m,n;

};



Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz *matriz=malloc(sizeof(Matriz));
  if (matriz == NULL) {
        printf("Error de memoria\n");
        return NULL;
    }

  matriz->array=malloc(sizeof(float)*numColumnas*numFilas);
  if (matriz->array == NULL) {
        printf("Error de memoria\n");
        free(matriz);
        return NULL;
    }
  matriz->m=numFilas;
  matriz->n=numColumnas;
  return matriz;
}

void matriz_destruir(Matriz* matriz) {
  if(matriz!=NULL){
    free(matriz->array);
    free(matriz);
    }
}

//un arreglo unidimensional, donde el elemento de la
// fila i y columna j es M [i ∗n + j], para todos 0 ≤i ≤m −1 y 0 ≤j ≤n −1
double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  if(matriz==NULL || fil>=matriz->m || col>=matriz->n ){return -0.1;}

  size_t x_y= fil * matriz->n + col;
  return (double) matriz->array[x_y];
  
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  if (matriz == NULL || fil >= matriz->m || col >= matriz->n) return;

  size_t indice= fil * matriz->n + col;
  matriz->array[indice]=(float) val;

}

size_t matriz_num_filas(Matriz* matriz) {
  if(matriz==NULL) return 0;
  return matriz->m;
}

size_t matriz_num_columnas(Matriz* matriz) {
  if(matriz==NULL) return 0;
  return matriz->n;
}

void matriz_intercambiar_filas(Matriz *matriz,size_t fila1, size_t fila2){
  if(matriz==NULL || fila1>=matriz->m || fila2>=matriz->m) return;
  
  size_t cols=matriz->m;

  for(size_t x= 0;x<cols;x++){
    size_t idx1=fila1*cols+x;
    size_t idx2=fila2*cols+x;

    float tmp=matriz->array[idx1];
    matriz->array[idx1]=matriz->array[idx2];
    matriz->array[idx2]=tmp;
  }

}

void matriz_agregar_fila(Matriz *matriz,size_t pos){
  if (!matriz || pos > matriz->m) return;

    size_t cols = matriz->n;
    size_t total_filas_nuevas = matriz->m + 1;
    size_t total_elementos_nuevos = total_filas_nuevas * cols;

    float *nuevo_array = realloc(matriz->array, sizeof(float) * total_elementos_nuevos);
    if (!nuevo_array) return;

    // Mover todas las filas posteriores una fila más abajo
    for (size_t i = matriz->m; i > pos; i--) {
        for (size_t j = 0; j < cols; j++) {
            size_t dest = i * cols + j;
            size_t src  = (i - 1) * cols + j;
            nuevo_array[dest] = nuevo_array[src];
        }
    }

    // Inicializar nueva fila en cero
    for (size_t j = 0; j < cols; j++) {
        nuevo_array[pos * cols + j] = 0.0;
    }

    matriz->array = nuevo_array;
    matriz->m++; // una fila más
    
}





