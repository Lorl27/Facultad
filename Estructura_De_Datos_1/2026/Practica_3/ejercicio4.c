// TAREA: usa glist para hacer cola.

#include "../Practica_2/glist/glist.h"
#include <stdio.h>
#include <stdlib.h>

typedef GList Cola;

Cola cola_crear(){
    Cola cola=glist_crear();
    return cola;
}

Cola Desencolar(Cola cola, FuncionDestructora destroy){
    cola=glist_eliminar_elemento_recursivamente(cola,destroy,0);
    return cola;
}

Cola Encolar(Cola cola , void * elemento, FuncionCopia copy){
    cola= insertar_final(cola,elemento,copy);
    return cola;
}

int isEmpty(Cola cola){
    return glist_vacia(cola);
}

Cola  cola_destruir(Cola cola,FuncionDestructora destroy){
    glist_destruir(cola,destroy);
    return NULL;
}

void cola_recorrer(Cola cola, FuncionVisitante fun){
    glist_recorrer(cola,fun);
}

void * Inicio(Cola cola){
    if (isEmpty(cola)) return NULL;
    return cola->data;
}