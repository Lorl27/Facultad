// Listas doblemente enlazadas
// 4. Implemente listas doblemente enlazadas de enteros y sus funciones b´asicas usando la siguiente definici´on.

#include <stdio.h>
#include "dlist.h"

void imprimir(int dato){
    printf("%d \t",dato);
}

int main() {
    DList lista = Dlist_crear();  
    lista = Dlist_agregar_final(lista, 10);
    lista = Dlist_agregar_final(lista, 20);
    lista = Dlist_agregar_final(lista, 30);
    lista=Dlist_agregar_inicio(lista,9000);

    Dlist_recorrer(lista,imprimir);
    printf("\nLongitud lista: %d\n\n",Dlist_longitud(lista));

    DList lista2 = Dlist_crear();
    lista2 = Dlist_agregar_final(lista2, 100);
    lista2 = Dlist_agregar_final(lista2, 200);
    lista2 = Dlist_agregar_final(lista2, 300);

    Dlist_concatenar(&lista,&lista2);
    Dlist_recorrer(lista,imprimir);

    // Destruir la lista
    Dlist_destruir(lista);

    return 0;
}
