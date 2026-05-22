#include <stdio.h>
#include <stdlib.h>

#include "../Practica_2/slist/slist.h"



SList slist_devolver_nodo_ciclo(SList lista){
    if(!lista || lista->sig==NULL) return NULL;

    SNodo * inicio=lista;
    SNodo * actual=lista;

    
    while(actual!=NULL && actual->sig!=NULL){
        inicio=inicio->sig;  // 1 paso
        actual=actual->sig->sig; //2 pasos

        if(actual==inicio){ //encontramos un ciclo!
            inicio=lista; // la reiniciamos

            while(inicio!=actual){
                inicio=inicio->sig;
                actual=actual->sig;
            }

            return actual; // se encontraron de nuevo!
        }
    }

    return NULL;
}


int main(){
    // 1 -> 2 -> 3 -> 4 -> (vuelve al 3)
    SNodo *n1 = malloc(sizeof(SNodo));
    SNodo *n2 = malloc(sizeof(SNodo));
    SNodo *n3 = malloc(sizeof(SNodo));
    SNodo *n4 = malloc(sizeof(SNodo));

    n1->dato = 1; n1->sig = n2;
    n2->dato = 2; n2->sig = n3;
    
    // NODO 3: Aquí empieza el ciclo
    n3->dato = 3; n3->sig = n4;
    
    n4->dato = 4; n4->sig = n3; 

    // Probamos nuestra función
    SList inicio_ciclo = slist_devolver_nodo_ciclo(n1);

    if (inicio_ciclo != NULL) {
        printf("¡Ciclo detectado! Empieza en el nodo con dato: %d\n", inicio_ciclo->dato);
    } else {
        printf("La lista no tiene ciclos.\n");
    }

    // Como tiene un ciclo, un destructor normal se quedaría en un bucle infinito borrando memoria.
    
    return 0;

}