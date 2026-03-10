#include "matriz.h"
#include <stdio.h>

/*
** Implementacion utilizando un arreglo bidimensional (arreglo de punteros a arreglo)
*/

struct Matriz_ {
  int m,n;  //m=fila ; n==col.
  float **array;
  
};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz *matriz=malloc(sizeof(Matriz));
  if(matriz==NULL){
    printf("fallo");
    return NULL;
  }

  matriz->m=numFilas;
  matriz->n=numColumnas;

  matriz->array=malloc(sizeof(float)*numFilas);
  if(matriz->array==NULL){
    printf("fallo");
    free(matriz);
    return NULL;
  }

  for(size_t x=0;x<numFilas;x++){
    matriz->array[x]=malloc(sizeof(float)*numColumnas);

    //si falla:
    if(matriz->array[x]==NULL){
      printf("fallo");
      for(size_t y=0;y<x;y++) free(matriz->array[y]);
      free(matriz->array);
      free(matriz);
      return NULL;
    }
  }


  return matriz;
}

void matriz_destruir(Matriz* matriz) {
  if(matriz!=NULL){
    for(size_t x=0;x<matriz->m;x++){
      free(matriz->array[x]);
    }
    free(matriz->array);
    free(matriz);
  }
}

//arreglo bidimensional, donde el elemento
// de la fila i y columna j es M [i][j]
double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  if(matriz==NULL || fil>=matriz->m || col>=matriz->n) return -0.1;

  return (double)matriz->array[fil][col];
  
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  if(matriz==NULL || fil>=matriz->m || col>=matriz->n) return ;
  matriz->array[fil][col]=(float)val;
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
  
  float *tmp=matriz->array[fila1];
  matriz->array[fila1]=matriz->array[fila2];
  matriz->array[fila2]=tmp;
}


void matriz_insertar_fila(Matriz *matriz, size_t pos) {
    if (!matriz || pos > matriz->m) return;

    // Crear nueva fila
    float *nueva_fila = malloc(sizeof(float) * matriz->n);
    if (!nueva_fila) return;

    // Inicializar nueva fila en 0 (opcional)
    for (size_t j = 0; j < matriz->n; j++) nueva_fila[j] = 0.0;

    // Aumentar array de punteros
    float **nuevo_array = realloc(matriz->array, sizeof(float *) * (matriz->m + 1));
    if (!nuevo_array) {
        free(nueva_fila);
        return;
    }

    // Desplazar filas hacia abajo
    for (size_t i = matriz->m; i > pos; i--) {
        nuevo_array[i] = nuevo_array[i - 1];
    }

    // Insertar nueva fila
    nuevo_array[pos] = nueva_fila;
    matriz->array = nuevo_array;
    matriz->m++; // una fila más
}
