// 8. Considere la siguiente definici´on de listas generales ordenadas
// typedef GList SGList;
// e implemente las siguientes funciones:
// a) SGList sglist crear() que retorna una lista ordenada vac´ıa.
// b) void sglist destruir(SGList, FuncionDestructora) que destruye una lista ordenada.
// c) int sglist vacia(SGList) que determina si una lista ordenada es vac´ıa.
// d) sglist recorrer(GList, FuncionVisitante) que aplica la funci´on visitante a cada elemento de
// la lista ordenada.
// e) SGList sglist insertar(SGList, void *, FuncionCopia, FuncionComparadora) que inserta
// un nuevo dato en la lista ordenada. La funci´on de comparaci´on es la que determina el criterio de
// ordenaci´on, su tipo est´a declarado como typedef int (*FuncionComparadora)(void *, void
// *), y retorna un entero negativo si el primer argumento es menor que el segundo, 0 si son iguales,
// y un entero positivo en caso contrario.
// f) int sglist buscar(GList, void *, FuncionComparadora) que busca un dato en la lista ordenada, retornando 1 si lo encuentra y 0 en caso contrario (aprovechar que la lista est´a ordenada para
// hacer esta b´usqueda m´as eficiente).
// g) SGList sglist arr(void **, int, FuncionCopia, FuncionComparadora) que construye una lista
// ordenada a partir de un arreglo de elementos y su longitud.


#include <stdio.h>
#include <stdlib.h>
#include "glist.h"
#include <assert.h>  

// Copia un entero
void *copiar_entero(void *dato) {
  int *nuevo = malloc(sizeof(int));
  *nuevo = *(int *)dato;
  return nuevo;
}

// Compara dos enteros
int comparar_enteros(void *a, void *b) {
  int x = *(int *)a;
  int y = *(int *)b;
  return x - y;
}

// Función auxiliar para copiar un int
void *copiar_int(void *dato) {
    int *nuevo = malloc(sizeof(int));
    *nuevo = *(int *)dato;
    return nuevo;
}

// Función auxiliar para comparar dos int
int comparar_ints(void *a, void *b) {
    return (*(int *)a - *(int *)b);
}

// Imprime un entero
void imprimir_entero(void *dato) {
  printf("%d ", *(int *)dato);
}

// Función para destruir el dato (en este caso, liberar el int)
void destruir_int(void *dato) {
    free(dato);
}

int main() {
  SGList lista = sglist_crear(); // crea lista vacía

  int valores[] = {5, 3, 8, 1, 4};
  int n = sizeof(valores)/sizeof(valores[0]);

  for (int i = 0; i < n; i++) {
    lista = sglist_insertar(lista, &valores[i], copiar_entero, comparar_enteros);
  }

  printf("Lista ordenada: ");
  sglist_recorrer(lista, imprimir_entero); // debe imprimir: 1 3 4 5 8
  printf("\n");

  // Liberar memoria
  sglist_destruir(lista, free);

  //---

  // Definir algunos enteros para usar en la lista
    int a = 5, b = 3, c = 8, d = 1, e = 4;
    void *arr[] = { &a, &b, &c, &d, &e };  // Array de enteros

    // Crear la lista ordenada a partir del array
    SGList lista1 = sglist_arr(arr, 5, copiar_int, comparar_ints);

    // Recorrer y mostrar la lista
    printf("Lista ordenada: ");
    sglist_recorrer(lista1, imprimir_entero);
    printf("\n");

    // Insertar un nuevo valor en la lista
    int f = 7;
    lista1 = sglist_insertar(lista1, &f, copiar_int, comparar_ints);

    // Mostrar la lista luego de la inserción
    printf("Lista después de insertar 7: ");
    sglist_recorrer(lista1, imprimir_entero);
    printf("\n");

    // Destruir la lista
    sglist_destruir(lista1, destruir_int);

    return 0;
}
