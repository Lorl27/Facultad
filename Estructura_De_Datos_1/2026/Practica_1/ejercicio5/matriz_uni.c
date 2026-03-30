#include "matriz.h"

// unidimensional fila i, col j: M[i*n+j]
// con i e [0,m-1] y j e [0,n-1]

/*
** Implmentacion utilizando un unico arreglo unidimensional
*/

struct Matriz_ {

  double * arreglo;
  size_t filas;
  size_t columnas;

};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
Matriz * matriz = malloc(sizeof(Matriz));
  if(matriz==NULL) return NULL;
  matriz->arreglo=malloc(sizeof(double)*(numFilas*numColumnas));
  if(matriz->arreglo==NULL){
    free(matriz);
    return NULL;
  }
  matriz->filas=numFilas;
  matriz->columnas=numColumnas;
  return matriz;
}

void matriz_destruir(Matriz* matriz) {
  if(matriz!=NULL){
    free(matriz->arreglo);
    free(matriz);
  }
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  if(matriz==NULL || fil>=matriz->filas || col>=matriz->columnas) return -1;
  return matriz->arreglo[col+matriz->columnas*fil];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  if(matriz!=NULL && fil<matriz->filas && col<matriz->columnas){
    matriz->arreglo[col+matriz->columnas*fil]=val;
  }
}

size_t matriz_num_filas(Matriz* matriz) {
  if(matriz==NULL) return -1;
return matriz->filas;
}

size_t matriz_num_columnas(Matriz* matriz) {
  if(matriz==NULL) return -1;
  return matriz->columnas;

}

void matriz_intercambiar_filas(Matriz * matriz,size_t fila_a, size_t fila_b){
  if(matriz!=NULL && fila_a<matriz->filas && fila_b<matriz->filas ){
    for (size_t columna = 0; columna < matriz->columnas; columna++) {
      double fila_quemada=matriz->arreglo[fila_a*matriz->columnas+columna];
      matriz->arreglo[fila_a*matriz->columnas+columna]=matriz->arreglo[fila_b*matriz->columnas+columna];
      matriz->arreglo[fila_b*matriz->columnas+columna]=fila_quemada;    
    }
  }
}

void matriz_insertar_fila(Matriz * matriz,int pos){
  if(matriz!=NULL && pos<=matriz->filas){
    // 1. Agrandamos el bloque gigante (+1 fila entera de tamaño 'columnas')
        size_t nueva_cantidad_total = (matriz->filas + 1) * matriz->columnas;
        double *nuevo_arreglo = realloc(matriz->arreglo, sizeof(double) * nueva_cantidad_total);
        if (nuevo_arreglo == NULL) return;
        matriz->arreglo = nuevo_arreglo;

        // 2. Empujamos los números uno por uno
        // ¿Cuántos números hay que mover? Todos los que están después de la fila 'pos'
        size_t inicio_hueco = pos * matriz->columnas;
        size_t fin_viejo = matriz->filas * matriz->columnas - 1;
        
        // Movemos de atrás para adelante, saltando el tamaño de una fila entera
        for (size_t i = fin_viejo + matriz->columnas; i > inicio_hueco + matriz->columnas - 1; i--) {
            matriz->arreglo[i] = matriz->arreglo[i - matriz->columnas];
        }
        
        // 3. (Opcional) Inicializar la nueva fila en 0.0
        for (size_t col = 0; col < matriz->columnas; col++) {
            matriz->arreglo[inicio_hueco + col] = 0.0;
        }

        matriz->filas++;
  }
}

/**
 * @file matriz_uni.c
 * @brief Implementación de matriz unidimensional para almacenamiento eficiente.
 * 
 * @details
 * Esta implementación utiliza un arreglo unidimensional para simular una matriz
 * bidimensional, optimizando el uso de memoria y el acceso a datos.
 * 
 * VENTAJAS:
 * - Máxima eficiencia de acceso: Al ser memoria contigua, es muy amigable 
 *   con el Caché del procesador (Spatial Locality).
 * - Menor consumo de memoria: Solo guarda los datos puros sin overhead adicional.
 * - Gestión simple: Solo requiere un malloc() y un free() para toda la matriz.
 * 
 * DESVENTAJAS:
 * - Cálculo manual: Obliga al programador a usar la fórmula matemática 
 *   [fila * n + col] en lugar de la sintaxis natural [fila][col].
 * - Menor legibilidad del código comparado con matrices multidimensionales.
 * 
 * @note El acceso a elementos requiere la conversión de índices 2D a 1D.
 */
