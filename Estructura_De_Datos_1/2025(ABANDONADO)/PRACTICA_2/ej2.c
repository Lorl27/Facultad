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

void slist_concatenar_recursiva(SList l1, SList l2) {
    if (l1 == NULL || l2 == NULL) return; 

    // Recorremos hasta el último nodo de l1 recursivamente
    if (l1->sig == NULL) {
        // Llegamos al final de l1, agregamos nodo con dato de l2
        SNodo* nuevo = malloc(sizeof(SNodo));
        nuevo->dato = l2->dato;
        nuevo->sig = NULL;
        l1->sig = nuevo;

        // Luego seguimos con el resto de l2
        slist_concatenar_recursiva(l1->sig, l2->sig);
    } else {
        slist_concatenar_recursiva(l1->sig, l2);
    }
}

int slist_longitud_recursiva(SList lista){

    if(lista==NULL) return 0;

    return 1 + slist_longitud_recursiva(lista->sig);
}

int slist_contiene_recursiva(SList lista, int dato){
    if(lista==NULL) return 1; //no esta

    if(lista->dato==dato){
        return 0;  //esta
    }

    return slist_contiene(lista->sig,dato);
}

int slist_indice_recursiva(SList lista, int elemento){
    if(lista==NULL) return -1;
    if (lista->dato==elemento) return 0;
    int indice=slist_indice_recursiva(lista->sig,elemento);

    if(indice==-1) return -1; //no lo encontro!.

    return indice +1;
}

SList slist_ordenar_recursiva(SList lista, FuncionComparadora comp) {
    if (lista == NULL || lista->sig == NULL) return lista;

    // Buscar el mínimo elemento en la lista y colocarlo al inicio
    SList menor = lista;
    SList actual = lista->sig;

    while (actual != NULL) {
        if (comp(actual->dato, menor->dato) < 0) {
            menor = actual;
        }
        actual = actual->sig;
    }

    // Intercambiar los datos entre el nodo menor encontrado y el primer nodo
    int tmp = lista->dato;
    lista->dato = menor->dato;
    menor->dato = tmp;

    // Aplicar recursión al resto de la lista (excepto el primer nodo que ya está ordenado)
    lista->sig = slist_ordenar_recursiva(lista->sig, comp);

    return lista;
}

SList slist_intercalar_recursiva(SList lista1, SList lista2) {
    if (lista1 == NULL && lista2 == NULL) return NULL;

    SList resultado = slist_crear();

    if (lista1 != NULL) {
        resultado = slist_agregar_inicio(resultado, lista1->dato);
        resultado->sig = slist_intercalar_recursiva(lista1->sig, lista2);
    } else if (lista2 != NULL) {
        resultado = slist_agregar_inicio(resultado, lista2->dato);
        resultado->sig = slist_intercalar_recursiva(lista1, lista2->sig);
    }

    return resultado;
}

SList slist_partir_recursiva(SList lista) {  //cuando slow (lista->sig->sig) llega al medio, es pq fast (lista->sig->sig->sig) llego al final.
    if (lista == NULL || lista->sig == NULL) return NULL;

    // Caso base: cuando fast o fast->sig llegó al final
    if (lista->sig->sig == NULL || lista->sig->sig->sig == NULL) {
        SList segunda_mitad = lista->sig;
        lista->sig = NULL; // Cortamos la lista
        return segunda_mitad;
    }

    // Llamada recursiva sobre el siguiente nodo
    SList mitad = slist_partir_recursiva(lista->sig);
    return mitad;
}


static void imprimir_entero(int dato) {
    printf("%d ", dato);
}

int comparar_enteros(int a, int b) {
    return a - b; // Orden ascendente
}

int comparar_desc(int a, int b) {
    return b - a;
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
    printf("Dsp de concatenar: \t");
    slist_recorrer(l, imprimir_entero);

    printf("\n--------");

    l2=slist_insertar(l2,55,3);
    printf("\n\nInserté elem en index 3: \t");
    slist_recorrer(l2, imprimir_entero);

    l2=slist_insertar(l2,0,1);
    printf("\n\nInserté elem en index 1: \t");
    slist_recorrer(l2, imprimir_entero);

    printf("\n-------- \n");

    l2=slist_eliminar(l2,0);
    printf("\nElimine elem en index 0: \t");
    slist_recorrer(l2, imprimir_entero);

    l2=slist_eliminar(l2,4);
    printf("\n\nElimine elem en index 4: \t");
    slist_recorrer(l2, imprimir_entero);

    l2=slist_eliminar(l2,3);
    printf("\n\nElimine elem en index 3: \t");
    slist_recorrer(l2, imprimir_entero);

    printf("\n--------\n");


    l2=slist_borrar_dato(l2,90);
    printf("\nElimine elem 90: \t");
    slist_recorrer(l2, imprimir_entero);

    l2=slist_borrar_dato(l2,0);
    printf("\n\nElimine elem 0: \t");
    slist_recorrer(l2, imprimir_entero);

    l2=slist_borrar_dato(l2,3);
    printf("\n\nElimine elem 3: \t");
    slist_recorrer(l2, imprimir_entero);

    printf("\n--------\n");

    int r1= slist_contiene(l2,10);
    int r2=slist_contiene(l2,0); 

    printf("L2+10 == %d , l2+0== %d\n",r1,r2);

    int r3=slist_indice(l,2);  //0
    int r4=slist_indice(l,11);  //1
    int r5=slist_indice(l,15);  //-1
    slist_agregar_final(l,10);  
    int r6=slist_indice(l,10);   //3


    printf("En L, estará... \n el elemento 2? ==> %d \n el elemento 11? ==> %d \n el elemento 15? ==> %d \n el elemento 10? ==> %d  \n",r3,r4,r5,r6); 
    printf("L1: \t");
    slist_recorrer(l, imprimir_entero); printf("\n--------\n");
    printf("L2: \t");
    slist_recorrer(l2, imprimir_entero); printf("\n--------\n");
    printf("Intersección entre ambos: \t");

    SList inter=slist_intersecar(l,l2);
    slist_recorrer(inter, imprimir_entero); printf("\n--------\n");
    
    SList l11 = slist_crear();
    SList l22 = slist_crear();

    l11 = slist_agregar_final(l11, 1);
    l11 = slist_agregar_final(l11, 2);
    l11 = slist_agregar_final(l11, 3);
    l11 = slist_agregar_final(l11, 4);

    l22 = slist_agregar_final(l22, 3);
    l22 = slist_agregar_final(l22, 4);
    l22 = slist_agregar_final(l22, 5);
    l22 = slist_agregar_final(l22, 6);

    printf("Lista 1: ");
    slist_recorrer(l11, imprimir_entero);
    printf("\n");

    printf("Lista 2: ");
    slist_recorrer(l22, imprimir_entero);
    printf("\n");

    SList interr = slist_intersecar(l11, l22);

    printf("Intersección: ");
    slist_recorrer(interr, imprimir_entero);
    printf("\n");

    //slist_destruir(l11);
    slist_destruir(l22);

    printf("\n--ORDENE LA LISTA:--- \t");
    slist_ordenar(interr,comparar_enteros);
    slist_recorrer(interr,imprimir_entero);

    printf("\n--ORDENE LA LISTA:--- \t");
    slist_ordenar(l,comparar_enteros);
    slist_recorrer(l,imprimir_entero);
    printf("\n--ORDENE LA LISTA (DESC):--- \t");
    slist_ordenar(l,comparar_desc);
    slist_recorrer(l,imprimir_entero);
    printf("\n--ORDENE LA LISTA recursivamente, again... --- \t");
    slist_ordenar_recursiva(l,comparar_enteros);
    slist_recorrer(l,imprimir_entero);
    printf("\nHe revertido l1: \t");
    slist_reverso(l11);
    slist_recorrer(l11,imprimir_entero);
    
    printf("\n\n Unimos todo: \t");
    SList m=slist_crear();
    m=slist_intercalar(l11,l);
    slist_recorrer(m,imprimir_entero);

    printf("\nDecidi dividirla: \t");
    slist_partir(l11);
    slist_recorrer(l11,imprimir_entero);

    printf("\nDecidi dividirla: \t");
    slist_partir(l);
    slist_recorrer(l,imprimir_entero);
    return 0;
}

