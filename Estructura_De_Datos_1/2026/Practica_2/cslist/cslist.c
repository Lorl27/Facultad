#include "cslist.h"
#include <stdio.h>
#include <stdlib.h>

CSList cslist_crear() {
  return NULL;
}

void cslist_destruir(CSList lista) {
    if (lista == NULL) return;
    SNodo *inicio = lista;
    SNodo *actual = lista;
    SNodo *tmp;
    do {
        tmp = actual;
        actual = actual->sig;
        free(tmp);
    } while (actual != inicio); 
}

int cslist_vacia(CSList lista) {
  return lista == NULL;
}

void cslist_recorrer(CSList lista, FuncionVisitante visit)
{
    SNodo *nodo = lista;
    do
    {
        visit(nodo->dato);
        nodo = nodo->sig;
    } while (nodo != lista);

}

int cslist_longitud(CSList lista){
  int contador=0;
    SNodo * inicio=lista;
  do{
    contador+=1;
    lista=lista->sig;
  }while(lista!=inicio);
  return contador;
}

CSList cslist_insertar_pos(CSList lista, int dato, int pos) {

    SNodo *nuevo = malloc(sizeof(SNodo));
    nuevo->dato = dato;

    // Caso A: Lista vacía (Nace el anillo)
    if (lista == NULL) {
        nuevo->sig = nuevo;
        return nuevo;
    }

    // Caso B: Ya hay elementos. Tenemos que buscar al último.
    SNodo *ultimo = lista;
    while (ultimo->sig != lista) { // Damos la vuelta hasta encontrar al que apunta al inicio
        ultimo = ultimo->sig;
    }

    if (pos == 0) {
     
        nuevo->sig = lista;
        ultimo->sig = nuevo;
        return nuevo;
    }

    if (lista == NULL) return lista; 

    SNodo *anterior = lista;      
    SNodo *actual = lista->sig;    
    
    int contador = 1;              

    while (contador < pos) {
        anterior = actual;         
        actual = actual->sig;      
        contador++;
    }

    if (contador == pos) {
        
        nuevo->sig = actual;       
        anterior->sig = nuevo;  
        
     
    }

    return lista;
}


CSList eliminar(CSList lista, int pos){
    if(lista == NULL || pos < 0 || pos >= cslist_longitud(lista)){ 
        return lista;
    }

    SNodo *ultimo = lista;
    while (ultimo->sig != lista) { // Damos la vuelta hasta encontrar al que apunta al inicio
        ultimo = ultimo->sig;
    }

    if(pos == 0){ 
        SNodo * tmp = lista;
        lista = lista->sig;
        ultimo->sig = lista;
        free(tmp);
        return lista;
    }

    SNodo *actual = lista;
    int contador = 1;
    while( contador < pos){
        actual = actual->sig;
        contador++;
    }

    if( contador == pos){
        
        SNodo * nodoAEliminar = actual->sig;
        
        actual->sig = nodoAEliminar->sig;
        
        free(nodoAEliminar);
    }

    return lista;
}

//si tenemos 1 2 3 , y hacemos agregar inicio(1), agregar inicio(2) -> 2 1
CSList cslist_reverso(CSList lista){
  CSList lista_reversa=cslist_crear();

  SNodo * tmp=lista;
  do{
      lista_reversa=cslist_agregar_inicio(lista_reversa,tmp->dato);
      tmp=tmp->sig;
  }while(tmp!=lista);
  
  return lista_reversa;
}