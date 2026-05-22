#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/slist/slist.h"

//Sufijo -> final de la lista
SList encontrar_sufijo_comun(SList lista1, SList lista2) {
    int len1 = slist_longitud(lista1);
    int len2 = slist_longitud(lista2);

    SNodo *p1 = lista1;
    SNodo *p2 = lista2;

    // 1. Alinear los punteros para que falte lo mismo para llegar al final
    while (len1 > len2) {
        p1 = p1->sig;
        len1--;
    }
    while (len2 > len1) {
        p2 = p2->sig;
        len2--;
    }

    SNodo *inicio_sufijo = NULL;

    // 2. Caminar a la par
    while (p1 != NULL && p2 != NULL) {
        if (p1->dato == p2->dato) {
            // Si coinciden y aún no habíamos marcado el inicio del sufijo, lo marcamos
            if (inicio_sufijo == NULL) {
                inicio_sufijo = p1; 
            }
        } else {
            // Si hay una diferencia, se rompe la racha. Anulamos el sufijo.
            inicio_sufijo = NULL;
        }
        
        // Avanzamos ambos a la par
        p1 = p1->sig;
        p2 = p2->sig;
    }

    // 3. Construimos una lista nueva con el resultado
    SList resultado = slist_crear();
    while (inicio_sufijo != NULL) {
        resultado = slist_agregar_final(resultado, inicio_sufijo->dato);
        inicio_sufijo = inicio_sufijo->sig;
    }

    return resultado;
}

// ==========================================
// FUNCIONES AUXILIARES PARA EL TEST
// ==========================================

// Usamos %c para imprimir el int como si fuera una letra
void imprimir_letra(int dato) {
    printf("%c -> ", dato);
}

SList crear_palabra(char *palabra) {
    SList lista = slist_crear();
    for (int i = 0; palabra[i] != '\0'; i++) {
        // Pasamos el caracter directamente, C lo convierte a int automaticamente
        lista = slist_agregar_final(lista, palabra[i]); 
    }
    return lista;
}

int main() {
    // Creamos las dos listas del ejemplo
    SList lista1 = crear_palabra("walking");
    SList lista2 = crear_palabra("listening");

    printf("Palabra 1: ");
    slist_recorrer(lista1, imprimir_letra);
    printf("NULL\n");

    printf("Palabra 2: ");
    slist_recorrer(lista2, imprimir_letra);
    printf("NULL\n");

    // Buscamos el sufijo
    SList sufijo = encontrar_sufijo_comun(lista1, lista2);

    printf("\nSufijo comun: ");
    if (slist_vacia(sufijo)) {
        printf("Ninguno\n");
    } else {
        slist_recorrer(sufijo, imprimir_letra);
        printf("NULL\n");
    }

    // Limpiamos memoria
    slist_destruir(lista1);
    slist_destruir(lista2);
    slist_destruir(sufijo);

    return 0;
}