#include <stdio.h>
#include <stdlib.h>
#include "cdlist.h"

// Nuestra función recorredora para imprimir
void imprimir_entero(int dato) {
    printf("[%d] <-> ", dato);
}

int main() {
    printf("=== INICIANDO PRUEBA DE LISTA CIRCULAR DOBLEMENTE ENLAZADA ===\n\n");

    // 1. Creación
    CDList mi_lista = crear();
    if (es_vacia(mi_lista)) {
        printf("[OK] La lista se creo vacia correctamente.\n\n");
    }

    // 2. Insertamos elementos desordenados
    printf("Insertando elementos (10, 20, 30, 40)...\n");
    mi_lista = insertar(mi_lista, 0, 30); // Lista: 30
    mi_lista = insertar(mi_lista, 0, 10); // Lista: 10, 30
    mi_lista = insertar(mi_lista, 1, 20); // Lista: 10, 20, 30
    mi_lista = insertar(mi_lista, 3, 40); // Lista: 10, 20, 30, 40

    printf("Longitud actual: %d\n\n", longitud(mi_lista));

    // 3. Recorridos automáticos (Probando tus do-while)
    printf("Recorrido HACIA ADELANTE:\n");
    recorrer(mi_lista, CDList_RECORRIDO_HACIA_ADELANTE, imprimir_entero);
    printf("(vuelve al %d...)\n\n", mi_lista->primero->dato);

    printf("Recorrido HACIA ATRAS:\n");
    recorrer(mi_lista, CDList_RECORRIDO_HACIA_ATRAS, imprimir_entero);
    printf("(vuelve al %d...)\n\n", mi_lista->primero->ant->dato);

    // 4. Prueba de demolición
    printf("Eliminando la posicion 1 (el numero 20)...\n");
    mi_lista = eliminar(mi_lista, 1);
    
    printf("Lista tras eliminar:\n");
    recorrer(mi_lista, CDList_RECORRIDO_HACIA_ADELANTE, imprimir_entero);
    printf("\n\n");

    

    // 5. ¡LA MAGIA CIRCULAR PURA!
    printf("=== DEMOSTRACION DEL ANILLO INFINITO ===\n");
    printf("Vamos a dar 8 pasos hacia adelante usando solo 'sig', sin importar la longitud:\n");
    
    // Accedemos a los nodos crudos (solo para probar)
    DNodo *viajero = mi_lista->primero;
    for(int i = 1; i <= 8; i++) {
        printf("%d -> ", viajero->dato);
        viajero = viajero->sig; // ¡Nunca es NULL!
    }
    printf("¡Infinito!\n\n");

    // 6. Prueba de Reverso
    printf("Probando la funcion reverso...\n");
    CDList lista_rev = reverso(mi_lista);
    recorrer(lista_rev, CDList_RECORRIDO_HACIA_ADELANTE, imprimir_entero);
    printf("\n\n");

    // 7. Limpieza final
    printf("Destruyendo las listas y liberando memoria...\n");
    destruir(mi_lista);
    destruir(lista_rev);
    printf("[OK] Memoria liberada. Prueba finalizada.\n");

    return 0;
}