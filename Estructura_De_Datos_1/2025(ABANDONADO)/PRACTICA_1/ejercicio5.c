// 5. Una matriz M de tama ̃no m ×n se puede definir como un arreglo bidimensional, donde el elemento
// de la fila i y columna j es M [i][j], o tambi ́en como un arreglo unidimensional, donde el elemento de la
// fila i y columna j es M [i ∗n + j], para todos 0 ≤i ≤m −1 y 0 ≤j ≤n −1

// a) Implemente el tipo de datos Matriz usando arreglos unidimensionales y bidimensionales de n ́umeros
// flotantes, junto a las operaciones b ́asicas asociadas (crear, destruir, escribir una posici ́on, leer de
// una posici ́on).
// A pesar de tener dos implementaciones distintas, las operaciones b ́asicas sobre una matriz son las
// mismas. Por dicha raz ́on queremos tener un  ́unico archivo de cabecera matriz.h, y un archivo .c
// por cada implementaci ́on: matriz uni.c y matriz bi.c.
// De esta forma, si tuvi ́eramos un programa main.c que utiliza matrices (incluye matriz.h), po-
// dremos optar por la implementaci ́on preferida en el momento de compilarlo.
// $gcc main.c matriz uni.c


// b) ¿Cu ́ales son las ventajas y desventajas de cada implementaci ́on?

/**
 *  Criterio	                Unidimensional	            Bidimensional
    Facilidad de acceso	        Menor (requiere cálculo)	Mayor ([i][j])
    Eficiencia de memoria	    Alta	                    Media
    Eficiencia de caché	        Alta	                    Baja
    Flexibilidad estructural	Menor	                    Mayor
    Complejidad de código	    Baja	                    Alta
    Limpieza de memoria	        Más fácil	                Más compleja
 */

// c) Defina una funci ́on matriz intercambiar filas, que intercambie dos filas dadas. ¿En cu ́al de las
// dos implementaciones anteriores resulta m ́as simple de definir? ¿Y para la operaci ́on
// matriz insertar fila, que agrega una nueva fila en una posici ́on dada?

// la más simple es la bidimencional, ya que funciona como un array normal.
// De nuevo, la más simple la bidimencional.

#include "matriz.h"
#include <stdio.h>



int main(){

    Matriz *m=matriz_crear(5,6);
    if(m==NULL) return 1;

    //escribir valores en m:
    for(size_t x=0;x<5;x++) {
        for(size_t y=0;y<6;y++) {
            matriz_escribir(m, x, y, (float)(x*10+y));
        }
    }

    printf("Contenido de la matriz:\n");
    for(size_t x=0;x<5;x++) {//filas
        for(size_t y=0;y<6;y++) {  //columnas
            double val = matriz_leer(m,x,y);
            printf("%5.1f ", val);
        }
        printf("\n");
    }

    size_t col=matriz_num_columnas(m);
    size_t fil=matriz_num_filas(m);
    printf("Hay %zu columnas y %zu filas\n", col,fil);

    printf("Modificamos M[2][2]\n");
    matriz_escribir(m,2,2,99000);
    printf("Ahora en la fila 2, col 2, esta: %.1f \n",matriz_leer(m,2,2));

    for(size_t x=0;x<5;x++) {//filas
        for(size_t y=0;y<6;y++) {  //columnas
            double val = matriz_leer(m,x,y);
            printf("%5.1f ", val);
        }
        printf("\n");
    }
    

    matriz_destruir(m);

    return 0;
}