#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//1)

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

//a.

GList glist_map ( GList lista , FuncionTransformar f , FuncionCopia c ){
    if(!lista) return NULL;
    GList new= glist_crear();

    for(GNodo * tmp=lista; tmp!=NULL; tmp=tmp->sig){
        new=glist_agregar_final(new,f(tmp->dato),c);
    }

    

    return new;
}


//b. 
void * stringMayuscula(void * c){
    char *str = (char *)c;
    for(int x=0;str[x]!='\0';x++){
        str[x]=toupper(str[x]);
    }
    return str;
}

//c.

GList mapeada= glist_map(lista,stringMayuscula,copia_string);

glist_destruir ( mapeada , dest_string ) ;



//2)


// Modifica la lista in-place (intercambiando punteros)
void merge_sort(SList *lista) {
    SList cabeza = *lista;

    // Caso base: si la lista está vacía o tiene 1 solo elemento, ya está ordenada.
    if (cabeza == NULL || cabeza->sig == NULL) {
        return;
    }

    // 1. DIVIDIR
    SList mitad_izq = cabeza;
    SList mitad_der = slist_partir(cabeza); // Corta 'cabeza' a la mitad y retorna el inicio de la segunda

    // 2. ORDENAR RECURSIVAMENTE
    merge_sort(&mitad_izq);
    merge_sort(&mitad_der);

    // 3. VENCER (Combinar)
    // Guardamos el resultado de la combinación como la nueva cabeza de la lista
    *lista = slist_intercalar_ordenado(mitad_izq, mitad_der);
}