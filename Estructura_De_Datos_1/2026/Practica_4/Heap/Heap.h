#ifndef __HEAP_H__
#define __HEAP_H__

typedef int (* FuncionComparadora)(void *a , void * b);
typedef void (* FuncionVisitante)(void * a);
typedef void (*FuncionDestructora)(void * a);
typedef void * (*FuncionCopiadora)(void * a);

typedef struct _BHeap {
    void ** arr;
    int capacidad;
    int ultimo;
} * BHeap;


/*
Crea un heap vacio con la capacidad dada 
*/
BHeap bheap_crear(int capacidad);

/*
Destruye el heap
*/
void bheap_destruir(BHeap heap,FuncionDestructora destroy);

/*
Retorna 1 si el Heap esta vacio,
0 en caso contrario
*/
int bheap_es_vacio(BHeap heap);

/* 
Recorre los nodos con Busqueda por extension, 
aplicando la funcion dada para cada elemento
*/
void bheap_recorrer(BHeap heap, FuncionVisitante visit);

/*
* Agrega un elemento al heap, respetando su estructura 
ademàs de reallocar en caso de ser necesario
*/
BHeap bheap_insertar(BHeap heap, void * elemento, FuncionCopiadora copy, FuncionComparadora comp);

/*
* Elimina un elemto del heap , respetando su estructura.
*/
BHeap bheap_eliminar_elemento(BHeap heap, void * elemento, FuncionComparadora comp, FuncionDestructora destroy);

/* Elimina el maximo, respetando la estrucutra del HEAP */
BHeap bheap_eliminar_maximo(BHeap heap, FuncionComparadora comp, FuncionDestructora destroy);

/*
* A partir de un arreglo arbitrario crea un heap binario
*/
BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copiar,FuncionComparadora comp);

// Retorna el elemento en la raíz del heap sin eliminarlo
void * bheap_obtener_maximo(BHeap heap);

#endif