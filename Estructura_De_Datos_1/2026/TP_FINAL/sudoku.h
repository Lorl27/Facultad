#ifndef __SUDOKU_H__
#define __SUDOKU_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Ejercicio 1: Definir una representación para el table de Sudoku (9x9)

#define MAX 9
#define MAX_CASILLAS 3
#define MAX_BORRAR 45
#define MAX_INTENTOS 10000

//Representa un tablero Sudoku de 9x9.
typedef struct _Sudoku{
    int tablero[MAX][MAX];
}Sudoku;

//Ejercicio 2: Implementar una función que reciba un tablero de Sudoku , parcialmente vacío, 
// y, devuelve 1 si tiene solución ó 0 si no.
// Cuando tenga solución: completar el tablero pasado con la misma.

/* Recibe un puntero del tablero de Sudoku (Para no hacer copias físicas)
Si cada fila contiene todos los números del 1 al 9 una única vez, retorna 1 (válido)
sino, 0.
*/
int validar_filas(const Sudoku * sudoku);

/* Recibe un puntero del tablero de Sudoku (Para no hacer copias físicas)
Si cada columna contiene todos los números del 1 al 9 una única vez, retorna 1 (válido)
sino, 0.
*/
int validar_columna(const Sudoku * sudoku);

/* Recibe un puntero del tablero de Sudoku (Para no hacer copias físicas)
Si un número dentro de una casilla (3x3) contiene todos los números del 1 al 9 una única vez, retorna 1 (válido)
sino, 0.
*/
int validar_casillas(const Sudoku * sudoku);

/* Recibe un puntero del tablero de Sudoku (Para no hacer copias físicas)
Si el tablero es válido retorna 1, 0 si no.
Se considera válido si:
- Un número dentro de una casilla (3x3) contiene todos los números del 1 al 9 una única vez
- Cada fila y columna, contiene todos los números del 1 al 9 una única vez
*/
int es_valido(const Sudoku * sudoku);

/*
Retorna 1 si es válido colocar tabla[fila][col]=num,
0 si no.
*/
int es_movimiento_valido(const Sudoku * sudoku, int fila, int columna, int numero);

/* Recorre recursivamente el tablero, buscando caminos correctos para la solución.
Busca la primera casilla vacía, para probar los números del 1 al 9
Si encuentra uno que no sirve, pasa al siguiente
Si probo todos y ninguno sirve: No tiene solución
*/
int tiene_solucion_aux(Sudoku * sudoku);

/* Recibe un puntero al tablero de Sudoku
- Retorna 0 si no tiene solución
- Retona 1 si la tiene, y completa el tablero pasado con la solución.
*/
int tiene_solucion(Sudoku * sudoku);

// Imprime en pantalla el sudoku pasado por párametro.
void imprimir_sudoku(const Sudoku * sudoku);

// Ejercicio 4: Modificar tiene_solucion para retornar
// 0: Si el Sudoku NO tiene soluciòn
// 1: Si el Sudoku tiene solución
// 2: Si tiene más de una solución


// Cuenta las soluciones que tiene el sudoku,
// y guarda el resultado en contador.
// NOTA: acá sería la modificación de tiene_solucion_aux
int contar_soluciones(Sudoku * sudoku, int * contador);

/* Recibe un puntero al tablero de Sudoku
- Retorna 0 si no tiene solución
- Retona 1 si la tiene, y completa el tablero pasado con la solución.
Retona 2 si tiene más de una, y completa el tablero pasado con la solución.
*/
int cantidad_soluciones(Sudoku * sudoku);

//Ejercicio 5: Implementar una función que devuelva un table de sudoku con solución única.
// Debe ser construido y no pre-calculado.


//Devuelve un tablero sudoku vacio.
Sudoku sudoku_crear(void);

//Devuelve un tablero sudoku aleatorio valido
Sudoku sudoku_aleatorio(void);

// Retorna un Sudoku que tiene una única solución.
Sudoku sudoku_con_unica_solucion(void);



#endif