#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/slist/slist.h"

// ==========================================
// FUNCION AUXILIAR: Invertir lista 
// ==========================================
SList invertir_lista(SList cabeza) {
    SNodo *anterior = NULL;
    SNodo *actual = cabeza;
    SNodo *siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->sig; 
        actual->sig = anterior;  
        anterior = actual;       
        actual = siguiente;      
    }
    return anterior; 
}

// ==========================================
// EL ALGORITMO PRINCIPAL
// ==========================================
int es_palindrome(SList lista) {
    if (lista == NULL || lista->sig == NULL) return 1; // Vacia o 1 letra siempre es palindrome

    // FASE 1: Buscar el centro
    SNodo *tortuga = lista;
    SNodo *liebre = lista;

    while (liebre != NULL && liebre->sig != NULL) {
        tortuga = tortuga->sig;
        liebre = liebre->sig->sig;
    }

    // Si la liebre no llegó a NULL, la lista es IMPAR. 
    // Ignoramos el nodo central adelantando la tortuga un paso más.
    if (liebre != NULL) {
        tortuga = tortuga->sig;
    }

    // FASE 2: Invertir la segunda mitad
    SNodo *segunda_mitad = invertir_lista(tortuga);
    SNodo *copia_segunda_mitad = segunda_mitad; // Guardamos para restaurar después 

    // FASE 3: Comparar
    SNodo *p1 = lista;
    SNodo *p2 = segunda_mitad;
    int resultado = 1; // Asumimos que es True (1)

    while (p2 != NULL) {
        if (p1->dato != p2->dato) {
            resultado = 0; // Falso, rompieron la simetría
            break;
        }
        p1 = p1->sig;
        p2 = p2->sig;
    }

    // Restaurar la lista original volviendo a invertir la segunda mitad
     invertir_lista(copia_segunda_mitad);

    return resultado;
}

// ==========================================
// FUNCIONES AUXILIARES PARA EL TEST
// ==========================================
void imprimir_letra(int dato) {
    printf("%c -> ", dato);
}

SList crear_palabra(char *palabra) {
    SList lista = slist_crear();
    for (int i = 0; palabra[i] != '\0'; i++) {
        lista = slist_agregar_final(lista, palabra[i]); 
    }
    return lista;
}

int main() {
    printf("=== TEST 1 (Impar) ===\n");
    SList lista1 = crear_palabra("kayak");
    printf("Entrada: ");
    slist_recorrer(lista1, imprimir_letra);
    printf("NULL\n");
    
    if (es_palindrome(lista1)) printf("Salida: True\n\n");
    else printf("Salida: False\n\n");


    printf("=== TEST 2 (Par) ===\n");
    SList lista2 = crear_palabra("anna");
    printf("Entrada: ");
    slist_recorrer(lista2, imprimir_letra);
    printf("NULL\n");
    
    if (es_palindrome(lista2)) printf("Salida: True\n\n");
    else printf("Salida: False\n\n");


    printf("=== TEST 3 (Falso) ===\n");
    SList lista3 = crear_palabra("perro");
    printf("Entrada: ");
    slist_recorrer(lista3, imprimir_letra);
    printf("NULL\n");
    
    if (es_palindrome(lista3)) printf("Salida: True\n\n");
    else printf("Salida: False\n\n");

    // Limpiamos
    slist_destruir(lista1);
    slist_destruir(lista2);
    slist_destruir(lista3);

    return 0;
}