#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/slist/slist.h"

// ==========================================
// FUNCION AUXILIAR: Invertir lista (ya que no podemos usar malloc.)
// ==========================================
// Toma una lista y da vuelta todas sus flechas (sig)
SList invertir_lista(SList lista) {
    SNodo *anterior = NULL;
    SNodo *actual = lista;
    SNodo *siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->sig; // Guardamos el resto
        actual->sig = anterior;  // Damos vuelta la flecha
        anterior = actual;       // Avanzamos
        actual = siguiente;      // Avanzamos
    }
    return anterior; // La nueva cabeza
}

// ==========================================
// EL ALGORITMO PRINCIPAL
// ==========================================
void reordenar_lista(SList lista) {
    // Si la lista tiene 0, 1 o 2 elementos, ya está ordenada según el patrón.
    if (lista == NULL || lista->sig == NULL || lista->sig->sig == NULL) return;

    // FASE 1: Encontrar la mitad (Tortuga y Liebre)
    SNodo *tortuga = lista;
    SNodo *liebre = lista;

    while (liebre->sig != NULL && liebre->sig->sig != NULL) {
        tortuga = tortuga->sig;
        liebre = liebre->sig->sig;
    }

    // FASE 2: Separar e invertir la segunda mitad
    SNodo *primera_mitad = lista;
    SNodo *segunda_mitad = tortuga->sig;
    tortuga->sig = NULL; // ¡CORTAMOS LA LISTA ORIGINAL!

    segunda_mitad = invertir_lista(segunda_mitad);

    // FASE 3: Entrelazar ambas mitades
    SNodo *p1 = primera_mitad;
    SNodo *p2 = segunda_mitad;

    while (p2 != NULL) {
        // Guardamos los siguientes nodos antes de romper los enlaces
        SNodo *siguiente_p1 = p1->sig;
        SNodo *siguiente_p2 = p2->sig;

        // Enganchamos: p1 -> p2 -> siguiente_p1
        p1->sig = p2;
        p2->sig = siguiente_p1;

        // Avanzamos los punteros para la siguiente vuelta
        p1 = siguiente_p1;
        p2 = siguiente_p2;
    }
}

// ==========================================
// FUNCIONES AUXILIARES PARA EL TEST
// ==========================================
void imprimir_entero(int dato) {
    printf("%d -> ", dato);
}

SList crear_desde_arreglo(int arr[], int tamano) {
    SList lista = slist_crear();
    for (int i = 0; i < tamano; i++) {
        lista = slist_agregar_final(lista, arr[i]);
    }
    return lista;
}

int main() {
    printf("=== TEST 1 (Impar) ===\n");
    int arr1[] = {1, 2, 3, 4, 5};
    SList lista1 = crear_desde_arreglo(arr1, 5);
    
    printf("Entrada: ");
    slist_recorrer(lista1, imprimir_entero);
    printf("NULL\n");
    
    reordenar_lista(lista1);
    
    printf("Salida:  ");
    slist_recorrer(lista1, imprimir_entero);
    printf("NULL\n");
    printf("Esperado: 1 -> 5 -> 2 -> 4 -> 3 -> NULL\n\n");


    printf("=== TEST 2 (Par) ===\n");
    int arr2[] = {1, 2, 3, 4, 5, 6};
    SList lista2 = crear_desde_arreglo(arr2, 6);
    
    printf("Entrada: ");
    slist_recorrer(lista2, imprimir_entero);
    printf("NULL\n");
    
    reordenar_lista(lista2);
    
    printf("Salida:  ");
    slist_recorrer(lista2, imprimir_entero);
    printf("NULL\n");
    printf("Esperado: 1 -> 6 -> 2 -> 5 -> 3 -> 4 -> NULL\n\n");

    slist_destruir(lista1);
    slist_destruir(lista2);

    return 0;
}