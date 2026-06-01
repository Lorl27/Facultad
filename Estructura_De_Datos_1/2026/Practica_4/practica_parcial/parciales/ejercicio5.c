#include <stdlib.h>

// --- Función Auxiliar 1: Divide y Vencerás para construir el AVL ---
AVL sorted_arr_to_avl_aux(void **arr, int inicio, int fin) {
    if (inicio > fin) return NULL;
    
    int medio = (inicio + fin) / 2;
    
    // Asumimos la estructura _AVL_Nodo con los campos estándar
    AVL nodo = malloc(sizeof(struct _AVL_Nodo));
    nodo->dato = arr[medio];
    
    nodo->izq = sorted_arr_to_avl_aux(arr, inicio, medio - 1);
    nodo->der = sorted_arr_to_avl_aux(arr, medio + 1, fin);
    
    int alt_izq = (nodo->izq != NULL) ? nodo->izq->altura : -1;
    int alt_der = (nodo->der != NULL) ? nodo->der->altura : -1;
    nodo->altura = 1 + ((alt_izq > alt_der) ? alt_izq : alt_der);
    
    return nodo;
}

// --- FUNCIÓN PRINCIPAL ---
