// 5. De una implementaci´on de listas doblemente enlazadas de enteros circulares. ¿Es necesario mantener
// un puntero al ´ultimo elemento de la lista? Llame a los ficheros como cdlist.h y cdlist.c. Implemente
// cdlist recorrer de manera que solo ejecute una pasada sobre cada elemento.

/**
 * 
 * En una lista doblemente enlazada circular, los nodos están conectados de manera que el primer nodo apunta al último, y el último nodo apunta de nuevo al primero. Esto permite recorrer la lista de forma circular sin necesidad de un marcador de fin. Sin embargo, la implementación puede ser más eficiente y más fácil de manejar si mantenemos un puntero al último elemento de la lista.

* ¿Es necesario mantener un puntero al último elemento?
En teoría, no es estrictamente necesario mantener un puntero al último nodo, ya que en una lista doblemente enlazada circular puedes acceder al último nodo a partir del primer nodo (ya que head->prev te da el último nodo). Sin embargo, para mayor eficiencia y simplicidad al implementar ciertas operaciones (como insertar al final, eliminar el último nodo, o recorrer la lista desde el último elemento), mantener un puntero al último nodo puede ser útil.
 * 
 */


#include <stdio.h>
#include "cdlist.h"

// Función visitante para imprimir
void imprimir(int dato) {
    printf("%d ", dato);
}

int main() {
    CDlist lista = Cdlist_crear();

    // Agrego algunos elementos al final
    lista = Cdlist_agregar_final(&lista, 10);
    lista = Cdlist_agregar_final(&lista, 20);
    lista = Cdlist_agregar_final(&lista, 30);

    // Agrego algunos elementos al inicio
    lista = Cdlist_agregar_inicio(&lista, 5);
    lista = Cdlist_agregar_inicio(&lista, 1);

    printf("Recorrido hacia adelante:\n");
    Cdlist_recorrer_elegir(lista, imprimir, CdLIST_RECORRIDO_HACIA_ADELANTE);
    printf("\n");

    printf("Recorrido hacia atras:\n");
    Cdlist_recorrer_elegir(lista, imprimir, CdLIST_RECORRIDO_HACIA_ATRAS);
    printf("\n");

    // Liberamos memoria
    Cdlist_destruir(&lista);

    return 0;
}


//TODO - Realizar las otras funciones...