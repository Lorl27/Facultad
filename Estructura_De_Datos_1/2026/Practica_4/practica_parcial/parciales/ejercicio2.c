#include <stdio.h>
#include <stdlib.h>

// --- Estructuras dadas en el examen ---
typedef struct {
    char *nombre, *club;
    int posicion, edad;
} _Jugador;

typedef _Jugador* Jugador;

typedef struct nodo {
    Jugador jug;
    struct nodo *izquierda, *derecha;
} Nodo;

// 1. FUNCION: agregaJugador (Inserción clásica de ABB)
Nodo* agregaJugador(Nodo* inicio, Jugador j) {
    // Caso base: llegamos a un hueco libre
    if (inicio == NULL) {
        Nodo* nuevo = malloc(sizeof(Nodo));
        nuevo->jug = j;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        return nuevo;
    }
    
    // Si la edad es menor, vamos a la izquierda
    if (j->edad < inicio->jug->edad) {
        inicio->izquierda = agregaJugador(inicio->izquierda, j);
    } 
    // Si la edad es mayor (o igual), vamos a la derecha
    else {
        inicio->derecha = agregaJugador(inicio->derecha, j);
    }
    
    return inicio;
}

// Función auxiliar para recorrer y filtrar (aprovechando que es un ABB)
void recupera_aux(Nodo* actual, int edadMax, int edadMin, Nodo** nuevo_arbol) {
    if (actual == NULL) return;

    // OPTIMIZACIÓN ABB: Si la edad actual es MAYOR a la mínima, 
    // vale la pena buscar en la rama izquierda.
    if (actual->jug->edad > edadMin) {
        recupera_aux(actual->izquierda, edadMax, edadMin, nuevo_arbol);
    }

    // Si el jugador actual está en el rango, lo agregamos al nuevo árbol
    // (¡Aquí hacemos uso de agregaJugador como sugirió Sampaoli!)
    if (actual->jug->edad >= edadMin && actual->jug->edad <= edadMax) {
        *nuevo_arbol = agregaJugador(*nuevo_arbol, actual->jug);
    }

    // OPTIMIZACIÓN ABB: Si la edad actual es MENOR a la máxima,
    // vale la pena buscar en la rama derecha.
    if (actual->jug->edad < edadMax) {
        recupera_aux(actual->derecha, edadMax, edadMin, nuevo_arbol);
    }
}

// 2. FUNCION: recuperaJugadoresPorEdad
Nodo* recuperaJugadoresPorEdad(Nodo* inicio, int edadMax, int edadMin) {
    // Validaciones pedidas por el enunciado en el main
    if (inicio == NULL || edadMax < edadMin) return NULL;

    Nodo* resultado = NULL;
    recupera_aux(inicio, edadMax, edadMin, &resultado);
    
    return resultado; // Retorna el nuevo árbol filtrado
}