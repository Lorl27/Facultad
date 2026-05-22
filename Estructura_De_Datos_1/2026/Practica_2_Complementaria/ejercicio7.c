#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/slist/slist.h"

//Podriamos haberlo hecho similar al 6.
SList encontrar_interseccion(SList lista1, SList lista2) {
    // Si alguna lista está vacía, es imposible que se intersecten
    if (lista1 == NULL || lista2 == NULL) return NULL;

    SNodo *p1 = lista1;
    SNodo *p2 = lista2;

    // Mientras no apunten exactamente a la misma dirección de memoria...
    while (p1 != p2) {
        // Si p1 llega a su fin, lo teletransportamos a la cabeza de la otra lista
        if (p1 == NULL) {
            p1 = lista2;
        } else {
            p1 = p1->sig;
        }

        // Si p2 llega a su fin, lo teletransportamos a la cabeza de la otra lista
        if (p2 == NULL) {
            p2 = lista1;
        } else {
            p2 = p2->sig;
        }
    }

    // Cuando el while termina, p1 y p2 son iguales.
    // Puede ser el nodo donde chocaron, o NULL si cruzaron todo y no había intersección.
    return p1;
}

// ==========================================
// FUNCIONES AUXILIARES
// ==========================================
void imprimir_entero(int dato) {
    printf("%d -> ", dato);
}

int main() {
    /* Vamos a construir manualmente este escenario:
       L1: 1 -> 2 -> 3 \
                        7 -> 8 -> 9
       L2:      5 -> 6 /
    */

    // 1. Creamos la "cola" compartida (7 -> 8 -> 9)
    SList cola_compartida = slist_crear();
    cola_compartida = slist_agregar_final(cola_compartida, 7);
    cola_compartida = slist_agregar_final(cola_compartida, 8);
    cola_compartida = slist_agregar_final(cola_compartida, 9);

    // 2. Creamos la cabeza de L1 (1 -> 2 -> 3)
    SList lista1 = slist_crear();
    lista1 = slist_agregar_final(lista1, 1);
    lista1 = slist_agregar_final(lista1, 2);
    lista1 = slist_agregar_final(lista1, 3);

    // Conectamos el final de L1 a la cola compartida
    SNodo *tmp = lista1;
    while(tmp->sig != NULL) tmp = tmp->sig;
    tmp->sig = cola_compartida;

    // 3. Creamos la cabeza de L2 (5 -> 6)
    SList lista2 = slist_crear();
    lista2 = slist_agregar_final(lista2, 5);
    lista2 = slist_agregar_final(lista2, 6);

    // Conectamos el final de L2 a la MISMA cola compartida
    tmp = lista2;
    while(tmp->sig != NULL) tmp = tmp->sig;
    tmp->sig = cola_compartida;

    // --- ESCENARIO LISTO ---
    printf("Lista 1 completa: ");
    slist_recorrer(lista1, imprimir_entero);
    printf("NULL\n");

    printf("Lista 2 completa: ");
    slist_recorrer(lista2, imprimir_entero);
    printf("NULL\n\n");

    // Ejecutamos la búsqueda
    SNodo *interseccion = encontrar_interseccion(lista1, lista2);

    if (interseccion != NULL) {
        printf("¡Interseccion encontrada en el nodo con valor: %d!\n", interseccion->dato);
    } else {
        printf("Las listas no se intersectan.\n");
    }

    // --- CUIDADO CON LA MEMORIA ---
    // Si haces slist_destruir(lista1) y slist_destruir(lista2), el tramo (7, 8, 9)
    // sufrirá un "Double Free" porque ambas listas intentarán borrarlo.
    // Solo destruiremos la primera lista completa, y de la segunda, solo los nodos únicos.
    
    tmp = lista2;
    while (tmp != cola_compartida) {
        SNodo *a_borrar = tmp;
        tmp = tmp->sig;
        free(a_borrar);
    }
    slist_destruir(lista1); // Esto destruirá 1, 2, 3 y también 7, 8, 9.

    return 0;
}