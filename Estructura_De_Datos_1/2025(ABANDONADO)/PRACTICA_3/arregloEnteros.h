typedef struct{
    int* direccion;
    int capacidad;
} ArregloEnteros;

/* Devuelve un arreglo de enteros, con la capacidad dada*/
ArregloEnteros* arreglo_enteros_crear(int capacidad);

/* Destruye el arreglo de enteros*/
void arreglo_enteros_destruir(ArregloEnteros* arreglo);

/* Retorna el elemento en la posición dada */
int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos);

/* Escribe el dato en la posicion dada*/
void arreglo_enteros_escribir(ArregloEnteros *arreglo, int pos, int dato);

/* Retorna la capacidad del arreglo*/
int arreglo_enteros_capacidad(ArregloEnteros *arreglo);

/* Imprime el arreglo*/
void arreglo_enteros_imprimir(ArregloEnteros *arreglo);

/* Ajusta la capacidad del arreglo*/
void arreglo_enteros_ajustar(ArregloEnteros *arreglo, int capacidad);

/* Inserta un elemento dado en la pos dada, mueve todos los elementos siguientes a la derecha */
void arreglo_enteros_insertar(ArregloEnteros *arreglo, int pos, int dato);

/* Elimina el elemento en al pos dada, moviendo todos los elementos siguientes a la izquierda*/
void arreglo_enteros_eliminar(ArregloEnteros *arreglo, int pos);