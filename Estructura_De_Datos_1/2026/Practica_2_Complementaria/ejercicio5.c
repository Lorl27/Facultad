#include <stdio.h>
#include <stdlib.h>

#include "../Practica_2/slist/slist.h"


SList eliminar_subsecuencias_cero(SList lista){
    // Creamos el Nodo Dummy (Centinela)
    // Esto nos salva la vida si la subsecuencia a borrar empieza en el primer nodo.
    SNodo *dummy = malloc(sizeof(SNodo));
    dummy->dato = 0;
    dummy->sig = lista;

    SNodo *actual = dummy;

    while (actual != NULL) {
        int suma = 0;
        SNodo *ultimo_cero = NULL;
        SNodo *temp = actual->sig;

        //Buscamos hacia adelante la secuencia MÁS LARGA que sume 0
        while (temp != NULL) {
            suma += temp->dato;
            if (suma == 0) {
                // Encontramos un tramo que suma 0. 
                // Actualizamos, pero NO CORTAMOS el bucle, por si hay un tramo más largo.
                ultimo_cero = temp; 
            }
            temp = temp->sig;
        }

        // Si encontramos alguna secuencia que sume 0
        if (ultimo_cero != NULL) {
            
            SNodo *destino = ultimo_cero->sig;

            // Liberamos la memoria de los nodos a borrar
            SNodo *borrar = actual->sig;
            while (borrar != destino) {
                SNodo *aux = borrar;
                borrar = borrar->sig;
                free(aux);
            }

            // Nos saltamos todo el bloque que sumaba cero
            actual->sig = destino;
            
            // NOTA CLAVE: Aquí NO avanzamos 'actual'. 
            // Nos quedamos parados en el mismo lugar porque al conectar la nueva 
            // parte de la lista, se podría haber formado un NUEVO bloque que sume 0.
        } 
        else {
            // Solo si revisamos todo y no hubo ninguna suma cero, avanzamos un paso.
            actual = actual->sig;
        }
    }

    // 4. Recuperamos la nueva cabecera verdadera y destruimos nuestro nodo ayudante
    SList nueva_cabeza = dummy->sig;
    free(dummy);

    return nueva_cabeza;
}


// ==========================================
// FUNCIONES AUXILIARES PARA EL TEST
// ==========================================

void imprimir_entero(int dato) {
    printf("%d -> ", dato);
}

// Crea una lista a partir de un arreglo 
SList crear_desde_arreglo(int arr[], int tamano) {
    SList lista = slist_crear();
    for (int i = 0; i < tamano; i++) {
        lista = slist_agregar_final(lista, arr[i]);
    }
    return lista;
}


int main() {
    printf("=== TEST 1 ===\n");
    int arr1[] = {6, -6, 8, 4, -12, 9, 8, -8};
    SList lista1 = crear_desde_arreglo(arr1, 8);
    
    printf("Entrada: ");
    slist_recorrer(lista1, imprimir_entero);
    printf("NULL\n");
    
    lista1 = eliminar_subsecuencias_cero(lista1);
    
    printf("Salida:  ");
    slist_recorrer(lista1, imprimir_entero);
    printf("NULL\n");
    printf("Esperado: 9 -> NULL\n\n");


    printf("=== TEST 2 ===\n");
    int arr2[] = {4, 6, -10, 8, 9, 10, -19, 10, -18, 20, 25};
    SList lista2 = crear_desde_arreglo(arr2, 11);
    
    printf("Entrada: ");
    slist_recorrer(lista2, imprimir_entero);
    printf("NULL\n");
    
    lista2 = eliminar_subsecuencias_cero(lista2);
    
    printf("Salida:  ");
    slist_recorrer(lista2, imprimir_entero);
    printf("NULL\n");
    printf("Esperado: 20 -> 25 -> NULL\n\n");

    slist_destruir(lista1);
    slist_destruir(lista2);

    return 0;
}