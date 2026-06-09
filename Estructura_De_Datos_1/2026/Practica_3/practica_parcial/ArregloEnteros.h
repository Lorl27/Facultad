#ifndef __ARREGLO_ENTEROS_H__
#define __ARREGLO_ENTEROS_H__

/*
 * Estructura que representa un arreglo dinámico de enteros.
 * - direccion: puntero al bloque de memoria donde se almacenan los enteros.
 * - capacidad: cantidad de elementos que puede contener el arreglo.
 */
typedef struct {
    int* direccion;
    int capacidad;
} ArregloEnteros;


/*
 * Crea un nuevo arreglo dinámico de enteros con la capacidad indicada.
 * Reserva memoria para la estructura y para el bloque de enteros.
 * Retorna un puntero al arreglo creado o NULL si falla la reserva.
 */
ArregloEnteros * arreglo_enteros_crear(int capacidad);

/*
 * Libera la memoria asociada al arreglo (tanto el bloque de enteros como la estructura).
 * Si el puntero es NULL, no hace nada.
 */
void arreglo_enteros_destruir(ArregloEnteros * arreglo);

/*
 * Devuelve el valor almacenado en la posición 'pos' del arreglo.
 * Si la posición es inválida o el arreglo es NULL, retorna -1.
 */
int arreglo_enteros_leer(ArregloEnteros * arreglo, int pos);

/*
 * Escribe el valor 'dato' en la posición 'pos' del arreglo.
 * Solo lo hace si la posición es válida y el arreglo no es NULL.
 */
void arreglo_enteros_escribir(ArregloEnteros * arreglo, int pos, int dato);

/*
 * Retorna la capacidad actual del arreglo (cantidad de elementos).
 * Si el arreglo es NULL, retorna 0.
 */
int arreglo_enteros_capacidad(ArregloEnteros  * arreglo);

/*
 * Imprime por consola todos los elementos del arreglo.
 * Si el arreglo es NULL, no hace nada.
 */
void arreglo_enteros_imprimir(ArregloEnteros * arreglo);

/*
 * Ajusta la capacidad del arreglo al nuevo tamaño indicado.
 * Usa realloc para redimensionar el bloque de memoria.
 * Si la operación falla, mantiene la capacidad anterior.
 */
void arreglo_enteros_ajustar(ArregloEnteros * arreglo, int nueva_capacidad);

/*
 * Inserta un nuevo elemento en la posición 'pos'.
 * Desplaza los elementos hacia la derecha para hacer espacio.
 * Aumenta la capacidad en 1.
 */
void arreglo_enteros_insertar(ArregloEnteros * arreglo, int pos, int dato);

/*
 * Elimina el elemento en la posición 'pos'.
 * Desplaza los elementos hacia la izquierda para tapar el hueco.
 * Reduce la capacidad en 1.
 */
void arreglo_enteros_eliminar(ArregloEnteros * arreglo, int pos);

#endif
