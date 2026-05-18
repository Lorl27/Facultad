#include "cslist_alternativa.h"
#include <stdlib.h>


CSList cslist_crear() {
    CSList creada = malloc(sizeof(CSListEstructura));

    if (creada == NULL) return NULL;

    creada->primero=NULL;
    creada->ultimo=NULL;

    return creada;
}

void cslist_destruir(CSList lista) {
        if (lista == NULL || lista->primero == NULL) { free(lista); return; }

        SNodo * inicio= lista->primero;
    SNodo *actual = lista->primero;
    SNodo *siguiente;

    do
    {
        siguiente = actual->sig;
        free(actual);
        actual=siguiente;
    }while (actual != inicio) ;
  
    free(lista);
}

int cslist_vacia(CSList lista) {
  return lista == NULL;
}

void cslist_recorrer(CSList lista, FuncionVisitante visit) {
    SNodo *nodo = lista->primero;
    do
    {
        visit(nodo->dato);
        nodo = nodo->sig;
    } while (nodo != lista->primero);
}

int cslist_longitud(CSList lista){
    if (lista == NULL) return 0;

    int contador=0;

    SNodo * tmp = lista->primero;
    do{
        contador++;
        tmp=tmp->sig;
    }while(tmp!=lista->primero);
    return contador;
}

CSList insertar(CSList lista,int pos, int dato){
    if(pos<0 || pos>longitud(lista)) return lista;

        SNodo * nuevo = malloc(sizeof(SNodo));
        nuevo->dato=dato;

    // Caso A: Nace el anillo
    if (lista->primero == NULL) {
        nuevo->sig = nuevo;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
        return lista;
    }

    if(pos==0){
        nuevo->sig=lista->primero;

        lista->primero=nuevo;

        lista->ultimo->sig = nuevo;

        return lista;
    }

    if(lista==NULL || lista->primero==NULL) return lista;

    SNodo * inicio=lista->primero;
    SNodo * actual=lista->primero->sig;
    int contador=1;

    while(contador<pos){
        inicio=actual;
        actual=actual->sig;
        contador++;
    }

    if(contador==pos){
        nuevo->sig=actual;
        inicio->sig=nuevo;

       // ¿Insertamos justo al final de la lista?
if (actual == lista->primero) { 
    lista->ultimo = nuevo; // Actualizamos el registro del final en la caja
}
    }

    return lista;
}


CSList cslist_eliminar_pos(CSList lista, int pos) {
    if(lista == NULL || lista->primero == NULL || pos < 0 || pos >= cslist_longitud(lista)) {
        return lista;
    }


    // Caso especial: Es el único nodo en el anillo
    if (lista->primero == lista->ultimo) {
        free(lista->primero);
        lista->primero = NULL;
        lista->ultimo = NULL;
        return lista;
    }

    if (pos == 0) {
        SNodo *tmp = lista->primero; 
        
        lista->primero = lista->primero->sig; 
        lista->ultimo->sig = lista->primero;
        
        if (lista->primero == NULL) {
            lista->ultimo = NULL;
        }
        
        free(tmp); 
        return lista;
    }

    int contador = 1;
    SNodo *inicio = lista->primero;         
    SNodo *actual = lista->primero->sig;    

    while (contador < pos) {
        inicio = actual;
        actual = actual->sig;
        contador++;
    }

    if (contador == pos ) {
        
        inicio->sig = actual->sig;
        
        // ¿Estábamos demoliendo el último nodo real de la lista?
if (actual == lista->ultimo) {
    lista->ultimo = inicio; // El nuevo final es el que estaba atrás
}
        
        free(actual); 
    }

    return lista;
}

//si tenemos 1 2 3 , y hacemos agregar inicio(1), agregar inicio(2) -> 2 1
CSList cslist_reverso(CSList lista){
  CSList lista_reversa=cslist_crear();

  SNodo * tmp=lista->primero;
  do{
      lista_reversa=cslist_agregar_inicio(lista_reversa,tmp->dato);
      tmp=tmp->sig;
  }while(tmp!=lista->primero);
  
  return lista_reversa;
}
