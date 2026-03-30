#ifndef __MATRIZ_H__
#define __MATRIZ_H__

#include <stdlib.h>

typedef struct Matriz_ Matriz;

/*
** Crea una nueva matriz
*/
Matriz* matriz_crear(size_t numFilas, size_t numColumnas);

/*
** Destruye una matriz
*/
void matriz_destruir(Matriz* matriz);

/*
** Obtiene el dato guardado en la posición dada de la matriz
*/
double matriz_leer(Matriz* matriz, size_t fil, size_t col);

/*
** Modifica el dato guardado en la posición dada de la matriz
*/
void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val);

/*
** Obtiene número de filas de la matriz
*/
size_t matriz_num_filas(Matriz* matriz);

/*
** Obtiene número de columnas de la matriz
*/
size_t matriz_num_columnas(Matriz* matriz);

/*
* Intercambia fila a con fila b
*/
void matriz_intercambiar_filas(Matriz * matriz,size_t fila_a, size_t fila_b);

/*
* Inseta una nueva fila en la posicion dada.
*/
void matriz_insertar_fila(Matriz * matriz,int pos);

#endif /* __MATRIZ_H__ */


/*
** ANÁLISIS: Implementación de Matriz (Bidimensional vs Unidimensional)
**
** INTERCAMBIO DE FILAS:
**   - Bidimensional (array de punteros): O(1)
**     Solo intercambia dos punteros, sin mover datos.
**   - Unidimensional (array plano): O(N)
**     Debe copiar elemento por elemento toda la fila.
**   → Ganador: Bidimensional
**
** INSERCIÓN DE FILA:
**   - Bidimensional: Simple
**     Redimensiona array de punteros, desplaza referencias.
**   - Unidimensional: Complejo
**     Requiere desplazar bloques masivos de memoria.
**     La aritmética de punteros es propensa a errores.
**   → Ganador: Bidimensional
**
** CONCLUSIÓN: La representación bidimensional es superior para
** operaciones que manipulan filas completas.
*/
