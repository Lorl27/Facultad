#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 5

typedef struct {
    int dato;
    int sig;  // Guarda el índice del siguiente nodo. -1 si es el final.
} NodoArreglo;

typedef struct {
    NodoArreglo *nodos; // El arreglo de nodos (nuestra "memoria RAM" privada)
    int capacidad;      // Cuántos lugares tenemos en total
    int cabeza;         // Índice donde empieza nuestra lista con datos (-1 si vacía)
    int primer_libre;   // Índice del primer lugar vacío disponible
} ListaArreglo;


ListaArreglo* crear_lista_arreglo() {
    ListaArreglo *lista = malloc(sizeof(ListaArreglo));
    lista->capacidad = CAPACIDAD_INICIAL;
    lista->nodos = malloc(sizeof(NodoArreglo) * lista->capacidad);
    
    lista->cabeza = -1;       // Nuestra lista de datos está vacía
    lista->primer_libre = 0;  // El primer lugar libre es el 0

    // Encadenamos todos los lugares libres entre sí
    for (int i = 0; i < lista->capacidad - 1; i++) {
        lista->nodos[i].sig = i + 1; // El 0 apunta al 1, el 1 al 2...
    }
    // El último lugar libre no tiene a nadie después
    lista->nodos[lista->capacidad - 1].sig = -1; 

    return lista;
}


int obtener_indice_libre(ListaArreglo *lista){
    if(lista->primer_libre!=-1){
        int indice_obtenido=lista->primer_libre;
        lista->primer_libre=lista->nodos[indice_obtenido].sig;
        return indice_obtenido;
    }

   int vieja_capacidad = lista->capacidad;
    lista->capacidad *= 2;

    lista->nodos = realloc(lista->nodos, sizeof(NodoArreglo) * lista->capacidad);

    // Enganchamos los NUEVOS lugares vacíos entre sí (del 5 al 9, por ejemplo)
        for (int i = vieja_capacidad; i < lista->capacidad - 1; i++) {
            lista->nodos[i].sig = i + 1;
        }

    lista->nodos[lista->capacidad - 1].sig = -1;

    lista->primer_libre = vieja_capacidad;

    int indice_obtenido = lista->primer_libre;
    lista->primer_libre = lista->nodos[indice_obtenido].sig;
    return indice_obtenido;

}


void insertar_inicio(ListaArreglo *lista, int dato){
    int indice_vacio=obtener_indice_libre(lista);
    lista->nodos[indice_vacio].dato=dato;

    lista->nodos[indice_vacio].sig = lista->cabeza;
    lista->cabeza = indice_vacio;
}