#include <stdio.h>
#include <stdlib.h>
#include "sglist.h"

// =================================================================
// 1. FUNCIONES AUXILIARES PARA ENTEROS (Cumpliendo el contrato void*)
// =================================================================

// COPIAR: Pide memoria nueva para un entero y le copia el valor original
void* copiar_entero(void* dato) {
    int *nuevo = malloc(sizeof(int));
    int *original = (int*)dato;
    *nuevo = *original;
    return nuevo;
}

// DESTRUIR: Simplemente libera la memoria del entero
void destruir_entero(void* dato) {
    free(dato);
}

// VISITAR: Convierte el void* a int* e imprime su valor
void imprimir_entero(void* dato) {
    int *numero = (int*)dato;
    printf("[%d] -> ", *numero);
}

// COMPARAR: Retorna <0 si a<b, 0 si a==b, >0 si a>b
int comparar_enteros(void* a, void* b) {
    int val_a = *(int*)a;
    int val_b = *(int*)b;
    
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

// =================================================================
// 2. EL CAMPO DE PRUEBAS
// =================================================================

int main() {
    printf("=== TEST 1: INSERCION ORDENADA ===\n");
    SGList lista = sglist_crear();
    
    // Variables locales para insertar (la lista hará sus propias copias)
    int n1 = 50, n2 = 10, n3 = 30, n4 = 20, n5 = 40;

    printf("Insertando los numeros desordenados: 50, 10, 30, 20, 40...\n");
    lista = sglist_insertar(lista, &n1, copiar_entero, comparar_enteros);
    lista = sglist_insertar(lista, &n2, copiar_entero, comparar_enteros);
    lista = sglist_insertar(lista, &n3, copiar_entero, comparar_enteros);
    lista = sglist_insertar(lista, &n4, copiar_entero, comparar_enteros);
    lista = sglist_insertar(lista, &n5, copiar_entero, comparar_enteros);

    printf("Resultado de la lista ordenada:\n");
    sglist_recorrer(lista, imprimir_entero);
    printf("NULL\n\n");

    
    printf("=== TEST 2: BUSQUEDA EFICIENTE ===\n");
    int buscar1 = 30;
    int buscar2 = 25;
    
    printf("Buscando el %d... ", buscar1);
    if (sglist_buscar(lista, &buscar1, comparar_enteros)) printf("ENCONTRADO!\n");
    else printf("No existe.\n");

    printf("Buscando el %d... ", buscar2);
    if (sglist_buscar(lista, &buscar2, comparar_enteros)) printf("ENCONTRADO!\n");
    else printf("No existe.\n");
    printf("\n");


    printf("=== TEST 3: CREAR LISTA DESDE UN ARREGLO ===\n");
    // Tenemos un arreglo de int normales
    int numeros_crudos[] = {99, 15, 42, 7, 88};
    int cantidad = 5;
    
    // Lo preparamos como un arreglo de void* (como pide la funcion)
    void* arreglo_punteros[5];
    for(int i = 0; i < cantidad; i++) {
        arreglo_punteros[i] = &numeros_crudos[i];
    }
    
    printf("Arreglo original: 99, 15, 42, 7, 88\n");
    SGList lista_desde_arr = sglist_arr(arreglo_punteros, cantidad, copiar_entero, comparar_enteros);
    
    printf("Lista ordenada generada desde el arreglo:\n");
    sglist_recorrer(lista_desde_arr, imprimir_entero);
    printf("NULL\n\n");


    // LIMPIEZA
    printf("=== LIMPIANDO MEMORIA ===\n");
    sglist_destruir(lista, destruir_entero);
    sglist_destruir(lista_desde_arr, destruir_entero);
    printf("Memoria liberada. ¡Todo perfecto!\n");

    return 0;
}