#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopiadora)(void *dato);

/** Retorna un entero negativo si dato1 < dato2,
 *  0 si son iguales y,
 *  un entero positivo si dato1 > dato2  */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);

/** Retorna un entero sin signo para el dato */
typedef unsigned (*FuncionHash)(void *dato);

typedef enum { VACIA, OCUPADA, ELIMINADA } EstadoCasilla;

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
  EstadoCasilla estado;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
typedef struct _TablaHash {
  CasillaHash * elementos;
  unsigned numElementos;
  unsigned capacidad;
  FuncionHash hash;
} * TablaHash;


/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad,FuncionHash hash);

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelementos(TablaHash tabla);

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla,FuncionDestructora destroy);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 *  IMPORTANTE: Maneja colisions con diccionario
 */
void tablahash_insertar(TablaHash tabla, void *dato, FuncionDestructora destroy, FuncionCopiadora copy,FuncionComparadora comp);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, 
 *  NULL si el dato  buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato,FuncionComparadora comp);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato,FuncionComparadora comp,FuncionDestructora destroy);

/*
Duplica la capacidad de la tabla y
 reposiciona todos los elementos de acuerdo a la nueva
posici´on que le asigne la funci´on de hash.
*/
void tablahash_redimensionar(TablaHash tabla) ;

#endif /* __TABLAHASH_H__ */