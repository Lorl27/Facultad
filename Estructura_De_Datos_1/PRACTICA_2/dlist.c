#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

DList Dlist_crear() {
    DList lista;
    lista.primero=NULL;
    lista.ultimo=NULL;

    return lista;
}

void Dlist_destruir(DList lista) {
    DNodo *tmp=lista.primero;

    while(tmp!=NULL){
        DNodo *siguiente= tmp->sig;
        free(tmp);
        tmp=siguiente;
    }
    
    lista.primero = NULL;
    lista.ultimo = NULL;

}

int Dlist_vacia(DList lista) {
    return (lista.primero==NULL && lista.ultimo==NULL);
}

DList Dlist_agregar_final(DList lista, int dato) {
    // Crear el nuevo nodo
    DNodo *nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = NULL;  
    nuevoNodo->ant = NULL;  

    // Si la lista está vacía...
    if (lista.primero == NULL) {
        lista.primero = nuevoNodo;
        lista.ultimo = nuevoNodo;
    } else {
        //actualizamos el anterior del último nodo
        lista.ultimo->sig = nuevoNodo;  // El antiguo último nodo apunta al nuevo
        nuevoNodo->ant = lista.ultimo;  // El nuevo nodo apunta al anterior último
        lista.ultimo = nuevoNodo;  // Ahora el último nodo es el nuevo nodo
    }

    return lista;  // Retornar la lista con el nuevo nodo agregado
}


DList Dlist_agregar_inicio(DList lista, int dato) {
    DNodo *nuevoNodo=malloc(sizeof(DNodo));
    nuevoNodo->dato=dato;
    nuevoNodo->sig=NULL;
    nuevoNodo->ant=NULL;

    if(lista.primero==NULL) {
        lista.primero=nuevoNodo;
        lista.ultimo=nuevoNodo;
    }else{
        lista.primero->ant=nuevoNodo;
        nuevoNodo->sig=lista.primero;
        lista.primero=nuevoNodo;
    }

    return lista;

}

void Dlist_recorrer(DList lista, FuncionVisitante visit) {
    if(Dlist_vacia(lista)) return;

    for(DNodo *tmp=lista.primero;tmp!=NULL;tmp=tmp->sig){
        visit(tmp->dato);
    }
}

//----

/* implemente dlist recorrer de manera
que se pueda elegir si se avanza o retrocede en el recorrido, utilizando el tipo:
typedef enum {
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
 } DListOrdenDeRecorrido; */
void Dlist_recorrer_elegir(DList lista,FuncionVisitante visit, DListOrdenDeRecorrido orden){

    if (Dlist_vacia(lista)) return;

    switch(orden){
        case DLIST_RECORRIDO_HACIA_ADELANTE:
            for(DNodo *tmp=lista.primero;tmp!=NULL;tmp=tmp->sig){
                visit(tmp->dato);
            }
            break;

        case DLIST_RECORRIDO_HACIA_ATRAS:
            for(DNodo *tmp=lista.ultimo;tmp!=NULL;tmp=tmp->ant){
                visit(tmp->dato);
            }
            break;
    }

}

//-----

int Dlist_longitud(DList lista){
    if(Dlist_vacia(lista)) return 0;

    int contador=0;
    for(DNodo *nodo=lista.primero;nodo!=NULL;nodo=nodo->sig){
        contador++;
    }

    return contador;
}

//-----------------------------

int Dlist_longitud_aux(DNodo *nodo) {
    if (nodo == NULL) return 0;
    return 1 + Dlist_longitud_aux(nodo->sig);
}

int Dlist_longitud_recursiva(DList lista) {
    if (Dlist_vacia(lista)) return 0;
    return Dlist_longitud_aux(lista.primero);
}

int Dlist_longitud_aux_atras(DNodo *nodo) {
    if (nodo == NULL) return 0;
    return 1 + Dlist_longitud_aux_atras(nodo->ant);
}

int Dlist_longitud_recursiva_hacia_atras(DList lista) {
    if (Dlist_vacia(lista)) return 0;
    return Dlist_longitud_aux_atras(lista.ultimo);
}

//-----------------------------

void Dlist_concatenar(DList *l1, DList *l2){
    if( l1== NULL || l2==NULL) return;
    
    if(l2->primero==NULL) return; //No podemos hacer nada

    if(l1->primero==NULL){ //entonces ponemos l2 en l1.
        l1->primero=l2->primero;
        l1->ultimo=l2->ultimo;
        return;
    }

    l1->ultimo->sig=l2->primero;
    l2->primero->ant=l1->ultimo;
    l1->ultimo=l2->ultimo;
}

void Dlist_insertar(DList *lista,int dato,int pos){
    if(lista==NULL || pos<0) return;

    DNodo *nodo=malloc(sizeof(DNodo));
    if(nodo==NULL) return;
    nodo->dato=dato;
    nodo->sig=NULL;
    nodo->ant=NULL;

    if(pos==0){
        nodo->sig=lista->primero;
        if(lista->primero!=NULL) lista->primero->ant=nodo;
        else lista->ultimo=nodo;  //estaba vacia

        lista->primero=nodo;
        return;
    }

    int conteo=0;
    DNodo *tmp;
    for(tmp=lista->primero;tmp!=NULL && conteo<pos-1 ;tmp=tmp->sig){ //vamos hasta antes de la pos
        conteo++;
    }

    if(tmp==NULL){  //nos fuimos del rango!
        free(nodo);
        return;
    }

    nodo->sig=tmp->sig;   //insertamos el nodo en medio
    nodo->ant=tmp;
    
    if(tmp->sig!=NULL) tmp->sig->ant = nodo;  //actualizamos al vecino (el ant)
    else lista->ultimo = nodo; // insertar al final

    tmp->sig = nodo; ///tmp=nodo anterior.

}

DList Dlist_eliminar_recursiva(DList lista, int pos){
    if(Dlist_vacia(lista) || pos<0) return lista;

    if(pos==0){
        DNodo *tmp=lista.primero;
        lista.primero=tmp->sig;

        if (lista.primero != NULL) lista.primero->ant = NULL;
        else                       lista.ultimo = NULL;

        free(tmp);
        return lista;
        
    }

    DList sublista;
    sublista.primero=lista.primero->sig;
    sublista.ultimo=lista.ultimo;

    sublista=Dlist_eliminar(sublista,pos-1);

    lista.primero->sig=sublista.primero;

    if(sublista.primero!=NULL) sublista.primero->ant=lista.primero;

    return lista;

}

DList Dlist_eliminar(DList lista, int pos) {
    if (Dlist_vacia(lista) || pos < 0) return lista;

    DNodo *actual = lista.primero;

    // Caso cuando se quiere eliminar el primer nodo
    if (pos == 0) {
        lista.primero = actual->sig;
        if (lista.primero != NULL) {
            lista.primero->ant = NULL;  // Actualizar el anterior del siguiente nodo
        } else {
            lista.ultimo = NULL;  // Si la lista quedó vacía, actualizar el último nodo
        }
        free(actual);  // Liberar memoria del nodo eliminado
        return lista;
    }

    // Iterar hasta llegar al nodo en la posición pos
    int i = 0;
    while (actual != NULL && i < pos) {
        actual = actual->sig;
        i++;
    }

    // Si no llegamos al nodo (pos fuera de rango)
    if (actual == NULL) return lista;

    // Conectar el nodo anterior con el siguiente (eliminar el nodo actual)
    actual->ant->sig = actual->sig;
    if (actual->sig != NULL) {
        actual->sig->ant = actual->ant;
    } else {
        lista.ultimo = actual->ant;  // Si eliminamos el último nodo, actualizar el último
    }

    free(actual);  // Liberar memoria del nodo eliminado
    return lista;
}



void Dlist_borrar_dato(DList *lista, int dato) {
    if (lista == NULL || lista->primero == NULL) return;

    DNodo *actual = lista->primero;

    while (actual != NULL) {
        if (actual->dato == dato) {
            DNodo *a_borrar = actual;

            if (actual->ant != NULL)
                actual->ant->sig = actual->sig;
            else
                lista->primero = actual->sig;  // era el primero

            if (actual->sig != NULL)
                actual->sig->ant = actual->ant;
            else
                lista->ultimo = actual->ant;  // era el último

            actual = actual->sig;  // avanzar antes de borrar
            free(a_borrar);
        } else {
            actual = actual->sig;
        }
    }
}


int Dlist_contiene(DList lista, int dato){
    if(Dlist_vacia(lista)) return -1;

    for(DNodo *tmp=lista.primero; tmp!=NULL;tmp=tmp->sig){
        if(tmp->dato==dato){
            return 0;
        }
    }

    return 1;  //No esta!
}

int Dlist_indice(DList lista, int elemento){
    if(Dlist_vacia(lista)) return -1;

    int index=0;
    for(DNodo *tmp=lista.primero;tmp!=NULL;tmp=tmp->sig){
        if(tmp->dato==elemento){
            return index;
        }
        index++;
    }

    return -1; //no encontrado...
}

DList Dlist_intersecar(DList dlista1, DList dlista2) {
    DList comunes = Dlist_crear();

    if (dlista1.primero == NULL || dlista2.primero == NULL) {
        return comunes;
    }

    for (DNodo* temp1 = dlista1.primero; temp1 != NULL; temp1 = temp1->sig) {
        // Verificamos si ya lo agregamos
        int ya_agregado = 0;
        for (DNodo* c = comunes.primero; c != NULL; c = c->sig) {
            if (c->dato == temp1->dato) {
                ya_agregado = 1;
                break;
            }
        }
        if (ya_agregado) continue;

        for (DNodo* temp2 = dlista2.primero; temp2 != NULL; temp2 = temp2->sig) {
            if (temp1->dato == temp2->dato) {
                comunes = Dlist_agregar_inicio(comunes, temp1->dato); // o agregar_final
                break;
            }
        }
    }

    return comunes;
}


DList Dlist_intersecar_custom(DList lista1, DList lista2, FuncionComparadora comp) {
    DList resultado = {NULL, NULL};

    for (DNodo *n1 = lista1.primero; n1 != NULL; n1 = n1->sig) {
        for (DNodo *n2 = lista2.primero; n2 != NULL; n2 = n2->sig) {
            if (comp(n1->dato, n2->dato) == 0) {
                // Agregar a resultado si no está repetido
                DNodo *nuevo = malloc(sizeof(DNodo));
                nuevo->dato = n1->dato;
                nuevo->sig = NULL;
                nuevo->ant = resultado.ultimo;

                if (resultado.ultimo)
                    resultado.ultimo->sig = nuevo;
                else
                    resultado.primero = nuevo;

                resultado.ultimo = nuevo;
                break; // Si ya lo agregamos, no seguir buscando
            }
        }
    }

    return resultado;
}

DList Dlist_ordenar(DList *lista, FuncionComparadora comp) {
    if (lista == NULL || lista->primero == NULL) return *lista;

    int cambiado;
    DNodo *actual;

    do {
        cambiado = 0;
        actual = lista->primero;

        while (actual != NULL && actual->sig != NULL) {
            if (comp(actual->dato, actual->sig->dato) > 0) {
                // Intercambiar datos
                int temp = actual->dato;
                actual->dato = actual->sig->dato;
                actual->sig->dato = temp;
                cambiado = 1;
            }
            actual = actual->sig;
        }

    } while (cambiado);

    return *lista;
}


DList Dlist_reverso(DList *lista){
    if(lista==NULL || lista->primero==NULL) return;

    DNodo *tmp;
    for(tmp=lista->primero;tmp!=NULL;tmp=tmp->ant){
            DNodo *aux=tmp->sig;
            tmp->sig=tmp->ant;
            tmp->ant=aux;
        }
    DNodo *aux=lista->primero;
    lista->primero=lista->ultimo;
    lista->ultimo=aux;
}

DList Dlist_intercalar(DList lista1, DList lista2) {
    DList resultado = {NULL, NULL};
    DNodo *n1 = lista1.primero;
    DNodo *n2 = lista2.primero;

    while (n1 != NULL || n2 != NULL) {
        if (n1 != NULL) {
            DNodo *nuevo = malloc(sizeof(DNodo));
            nuevo->dato = n1->dato;
            nuevo->sig = NULL;
            nuevo->ant = resultado.ultimo;

            if (resultado.ultimo)
                resultado.ultimo->sig = nuevo;
            else
                resultado.primero = nuevo;

            resultado.ultimo = nuevo;
            n1 = n1->sig;
        }

        if (n2 != NULL) {
            DNodo *nuevo = malloc(sizeof(DNodo));
            nuevo->dato = n2->dato;
            nuevo->sig = NULL;
            nuevo->ant = resultado.ultimo;

            if (resultado.ultimo)
                resultado.ultimo->sig = nuevo;
            else
                resultado.primero = nuevo;

            resultado.ultimo = nuevo;
            n2 = n2->sig;
        }
    }

    return resultado;
}



DList Dlist_partir(DList *lista) {
    DList segunda = {NULL, NULL};
    if (lista == NULL || lista->primero == NULL) return segunda;

    int len = 0;
    DNodo *tmp = lista->primero;
    while (tmp != NULL) {
        len++;
        tmp = tmp->sig;
    }

    int mitad = len / 2;
    tmp = lista->primero;
    for (int i = 0; i < mitad; i++) {
        tmp = tmp->sig;
    }

    if (tmp == NULL) return segunda;

    segunda.primero = tmp;
    segunda.ultimo = lista->ultimo;

    if (tmp->ant) {
        tmp->ant->sig = NULL;
        lista->ultimo = tmp->ant;
        tmp->ant = NULL;
    }

    return segunda;
}


//NOTE - RETOMAR LUEGO, ENTENDIENDO BIEN TODO.
//TODO - Rehacer ejercicios ">..."

