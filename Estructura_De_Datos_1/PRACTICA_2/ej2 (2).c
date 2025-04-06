// 2. Extienda la implementaci´on anterior con las siguientes funciones:
// a) slist longitud que devuelve la longitud de una lista.
// b) slist concatenar que devuelve la concatenaci´on de dos listas, modificando la primera.
// c) slist insertar que inserta un dato en una lista en una posici´on arbitraria.
// d) slist eliminar que borra de una lista un dato apuntado en una posici´on arbitraria.
// e) slist contiene que determina si un elemento est´a en una lista dada.
// f ) slist indice que devuelve la posici´on de la primera ocurrencia de un elemento si el mismo est´a en
// la lista dada, y -1 en caso que no est´e.
// g) slist intersecar que devuelve una nueva lista con los elementos comunes (independientemente de
// la posici´on) de dos listas dadas por par´ametro. Las listas originales no se modifican.
// h) slist intersecar custom que trabaja como la anterior pero recibe un par´ametro extra que es un
// puntero a una funci´on de comparaci´on que permite definir la noci´on de igualdad a ser usada al
// comparar elementos por igualdad.
// i) slist ordenar que ordena una lista de acuerdo al criterio dado por una funci´on de comparaci´on
// (que usa los mismos valores de retorno que strcmp()) pasada por par´ametro.
// j) slist reverso que obtenga el reverso de una lista.
// k) slist intercalar que dadas dos listas, intercale sus elementos en la lista resultante. Por ejemplo,
// dadas las listas [1, 2, 3, 4] y [5, 6], debe obtener la lista [1, 5, 2, 6, 3, 4].
// l) slist partir que divide una lista a la mitad. En caso de longitud impar (2n + 1), la primer lista
// tendr´a longitud n + 1 y la segunda n. Retorna un puntero al primer elemento de la segunda mitad,
// siempre que sea no vac´ıa.
// Indique cu´ales son las operaciones que piensa que m´as tiempo consumen en ejecutarse. ¿Cu´ales de ellas
// dependen del tama˜no de sus argumentos?

#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

// int slist_longitud(SList lista){
//     int cont=0;

//     if(lista==NULL){
//         printf("Lista vacía");
//         return 0;
//     }

//     for(SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
//         cont++;
//     }

//     return cont;
// }

//--------

// void slist_concatenar(SList l1, SList l2){

//      for(SNodo *nodo = l2; nodo != NULL; nodo = nodo->sig){
//         // printf("%d",nodo->dato);
//         slist_agregar_final(l1,nodo->dato);

//     }
// }


//----

// SList slist_insertar(SList lista,int dato,int pos){
//     SNodo *tmp = malloc(sizeof(SNodo));
//     SNodo *newN = malloc(sizeof(SNodo));
    
//     int contador=0;

//     for(SNodo *nodo =lista; nodo!=NULL; nodo=nodo->sig){
//         contador++;
//         if(contador==pos){
//             tmp=nodo->sig;
//             nodo->sig=newN;
//             newN->dato=dato;
//             newN->sig=tmp;
//         }
        
//     }

//     return lista;
// }

//----

/* ARREGLAR! la primera it. repite elemento sig.*/
//borra de la lista, el elemento en pos.
SList slist_eliminar(SList lista, int pos){
    int contador=0;

    SNodo *tmp=malloc(sizeof(SNodo));

    if(pos==0){ //tengo q mover + destruir + dup2
        tmp=lista->sig; //muevo inicio
        
        slist_destruir(lista);
        
        lista=tmp;

        return lista;
    }

    for(SNodo *nodo=lista;nodo!=NULL;nodo=nodo->sig){
        if(contador==pos){
            nodo->dato=nodo->sig->dato;
        }

        contador++;
        
    }

    return lista;
}


static void imprimir_entero(int dato) {
    printf("%d ", dato);
}


int main(){
    SList l=slist_crear();
    l=slist_agregar_inicio(l,11);
    l=slist_agregar_inicio(l,2);

    SList l2=slist_crear();
    l2=slist_agregar_inicio(l2,10);
    l2=slist_agregar_inicio(l2,28);
    l2=slist_agregar_final(l2,90);
    l2=slist_agregar_final(l2,10489);

    int r=slist_longitud(l);
    printf("Longitud de la lista: %d\n", r);

    printf("Lista 1: \t");
    slist_recorrer(l, imprimir_entero);

    printf("\n");

    printf("Lista 2: \t");
    slist_recorrer(l2, imprimir_entero);

    printf("\n\n");

    if(l==NULL || l2==NULL){
        printf("Listas vacías.\n");
        return 1;
    }

    slist_concatenar(l,l2);
    printf("Dsp de concatenar: ");
    slist_recorrer(l, imprimir_entero);

    printf("--------");

    l2=slist_insertar(l2,55,3);
    printf("\n\nInserté elem en index 3 \n");
    slist_recorrer(l2, imprimir_entero);
    
    l2=slist_insertar(l2,0,1);
    printf("\n\nInserté elem en index 1 \n");
    slist_recorrer(l2, imprimir_entero);

    printf("\n-------- \n");

    l2=slist_eliminar(l2,0);
    printf("\nElimine elem en index 0 \n");
    slist_recorrer(l2, imprimir_entero);

    l2=slist_eliminar(l2,4);
    printf("\n\nElimine elem en index 4 \n");
    slist_recorrer(l2, imprimir_entero);

    l2=slist_eliminar(l2,3);
    printf("\n\nElimine elem en index 3 \n");
    slist_recorrer(l2, imprimir_entero);

    printf("\n--------\n");

    return 0;
}

