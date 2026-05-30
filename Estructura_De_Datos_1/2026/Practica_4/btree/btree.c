#include "btree.h"
#include <assert.h>
#include <stdlib.h>
#include "../Practica_3/Pila/pila.h"
#include "../Practica_3/Cola/cola.h"

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() {
   return NULL;
}

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo,FuncionDestructora destroy) {
  if (nodo != NULL) {
    btree_destruir(nodo->izq,destroy);
    btree_destruir(nodo->der,destroy);
    destroy(nodo->dato);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) {
    return nodo == NULL; 
}

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void * dato, BTree left, BTree right, FuncionCopia copy) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  if(nuevoNodo!=NULL){
    nuevoNodo->dato = copy(dato);
    nuevoNodo->izq = left;
    nuevoNodo->der = right;
  }
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,FuncionVisitante visit) {
  if(btree_empty(arbol)) return;

  if(orden==BTREE_RECORRIDO_IN){
    btree_recorrer(arbol->izq,orden,visit);
    visit(arbol->dato);
    btree_recorrer(arbol->der,orden,visit);
  }

  if(orden==BTREE_RECORRIDO_POST){
    btree_recorrer(arbol->izq,orden,visit);
    btree_recorrer(arbol->der,orden,visit);
    visit(arbol->dato);
  }

  if(orden==BTREE_RECORRIDO_PRE){
    visit(arbol->dato);
    btree_recorrer(arbol->izq,orden,visit);
    btree_recorrer(arbol->der,orden,visit);
  }
  
}


//al ser general la pila, hacemos lo sig (fun dummys!):
void * copiar_puntero_btree(void * nodo) {
    return nodo; 
}

void no_destruir_nada(void * nodo) {
    // nada
}

void btree_recorrer_iterativo(BTree arbol,FuncionVisitante visit){
    if(btree_empty(arbol)) return ;


    Pila pila=pila_crear();

    pila=Push(pila,arbol,copiar_puntero_btree);

    while(!isEmpty(pila)){
      BTNodo * nodo=(BTree)Top(pila);
      pila=Pop(pila,no_destruir_nada);

      visit(nodo->dato);

      //Primero der , asi en la prox vuelta el izq esta arriba.
      if(nodo->der!=NULL){
        pila=Push(pila,nodo->der,copiar_puntero_btree);
      }

      if(nodo->izq!=NULL){
        pila=Push(pila,nodo->izq,copiar_puntero_btree);
      }

    }

    pila=pila_destruir(pila,no_destruir_nada);
}


int btree_nnodos(BTree arbol){
  if (btree_empty(arbol)) return 0;

  return 1 + btree_nnodos(arbol->der) + btree_nnodos(arbol->izq);
  
}

int btree_buscar(BTree arbol, void * numero, FuncionComparadora fun){
  if(btree_empty(arbol)) return 0;
  
  int comparacion=fun(arbol->dato,numero);
  if(comparacion==0) return 1;

  return btree_buscar(arbol->izq,numero,fun) || btee_buscar(arbol->der,numero,fun);
}


BTree btree_copiar(BTree arbol,FuncionCopia copy){

  if(btree_empty(arbol)) return NULL;

  return btree_unir(arbol->dato, btree_copiar(arbol->izq, copy), btree_copiar(arbol->der, copy), copy);
}

int btree_altura(BTree arbol){
  if(btree_empty(arbol)) return -1;

  int alt_izq = btree_altura(arbol->izq);
  int alt_der = btree_altura(arbol->der);

  if (alt_izq > alt_der) return 1 + alt_izq;
  else return 1 + alt_der;
}

int btree_nnodos_profundidad(BTree arbol,int profundidad){
  if(btree_empty(arbol)) return 0;

  if(profundidad==0) return 1;

  return btree_nnodos_profundidad(arbol->izq,(profundidad-1)) + btree_nnodos_profundidad(arbol->der,(profundidad-1));
}


int btree_profundidad(BTree arbol, void * numero,FuncionComparadora fun){
  if(btree_empty(arbol)) return -1;

  if(fun(arbol->dato, numero) == 0) return 0;

  // Busco en la izquierda
  int prof_izq = btree_profundidad(arbol->izq, numero, fun);
  if (prof_izq != -1) return 1 + prof_izq; // Si lo encontró a la izquierda, le sumo 1 paso

  // Si no estaba en la izquierda, busco en la derecha
  int prof_der = btree_profundidad(arbol->der, numero, fun);
  if (prof_der != -1) return 1 + prof_der; // Si lo encontró a la derecha, le sumo 1 paso

  return -1; //no estaba en ninguin lado...
}


// void * btree_sumar(BTree arbol, FuncionSuma sum){
//   if(btree_empty(arbol)) return NULL;

//   return sum(arbol->dato,( sum(btree_sumar(arbol->izq,sum) ,btree_sumar(arbol->der,sum))));
// }

//esta bueno el anterior, pero produce fugas de memoria luego...
// mejor this:

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,FuncionVisitanteExtra visit, void * extra) {
    if (btree_empty(arbol)) return;
    
    if(orden==BTREE_RECORRIDO_IN){
      btree_recorrer_extra(arbol->izq,orden, visit, extra);
      visit(arbol->dato, extra); 
      btree_recorrer_extra(arbol->der, orden,visit, extra);
    }

    if(orden==BTREE_RECORRIDO_POST){
      btree_recorrer_extra(arbol->izq,orden, visit, extra);
      btree_recorrer_extra(arbol->der, orden,visit, extra);
    visit(arbol->dato, extra); 
    }

    if(orden==BTREE_RECORRIDO_PRE){
      visit(arbol->dato, extra);
      btree_recorrer_extra(arbol->izq,orden, visit, extra);
      btree_recorrer_extra(arbol->der, orden,visit, extra);
    }
}




void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit) {
    // Si el árbol está vacío, no hacemos nada
    if (btree_empty(arbol)) return;

    // 1. Creamos la "sala de espera"
    Cola sala_espera = Cola_crear();

    // 2. El primer paciente en la fila es la raíz
    sala_espera = Encolar(sala_espera, arbol, copiar_puntero_btree);

    // 3. Mientras haya gente en la sala de espera...
    while (!isEmpty(sala_espera)) {
        // Atendemos al que está al inicio de la fila
        BTree actual = (BTree)sala_espera->fin;
        sala_espera = Desencolar(sala_espera, no_destruir_nada);

        // Lo visitamos (procesamos su dato)
        visit(actual->dato);

        // Si este paciente tiene "hijos", los mandamos a hacer fila AL FINAL
        // ¡Ojo al orden! Como recorremos de Izquierda a Derecha, 
        // encolamos primero el izquierdo.
        if (actual->izq != NULL) {
            sala_espera = Encolar(sala_espera, actual->izq, copiar_puntero_btree);
        }
        
        if (actual->der != NULL) {
            sala_espera = Encolar(sala_espera, actual->der, copiar_puntero_btree);
        }
    }

    // Cerramos la sala de espera
    cola_destruir(sala_espera, no_destruir_nada);
}

int btree_contar_hojas(BTree arbol){
  if(btree_empty(arbol)) return 0;

  //soy una hoja
  if(btree_empty(arbol->izq) && btree_empty(arbol->der) )return 1 ;

  return  btree_contar_hojas(arbol->izq) + btree_contar_hojas(arbol->der);
}

int btree_son_iguales(BTree arbol1, BTree arbol2, FuncionComparadora comp){

  if(btree_empty(arbol1) && btree_empty(arbol2)) return 1;

  if(!btree_empty(arbol2)|| !btree_empty(arbol1) ) return 0;

  if(comp(arbol1->dato,arbol2->dato)!=0 ) return 0;

  
  return btree_son_iguales(arbol1->izq,arbol2->izq,comp) && btree_son_iguales(arbol1->der, arbol2->der, comp);

  return 0;
}


int btree_contar_un_hijo(BTree arbol){
  if(btree_empty(arbol)) return 0;

  int soy_padre_soltero = 0;

  //? tengo 1 solo hijo?:
  if(!btree_empty(arbol->der)&&btree_empty(arbol->izq) || btree_empty(arbol->der)&&!btree_empty(arbol->izq)) soy_padre_soltero=1;

  return soy_padre_soltero + btree_contar_un_hijo(arbol->izq) + btree_contar_un_hijo(arbol->der);
}

int btree_es_estricto(BTree arbol){
  if(btree_empty(arbol)) return 1;

  //tengo algun nodo con un hijo?...
  if(btree_contar_un_hijo(arbol)!=0) return 0;

  return 1;
}

int btree_es_estricto_V2(BTree arbol){
    if(btree_empty(arbol)) return 1;
    
    // Si soy hoja (0 hijos), cumplo la regla
    if(btree_empty(arbol->izq) && btree_empty(arbol->der)) return 1;
    
    // Si tengo 1 solo hijo, rompo la regla. ¡Corto el proceso y devuelvo 0!
    if(btree_empty(arbol->izq) || btree_empty(arbol->der)) return 0;
    
    // Si llegué acá, tengo 2 hijos. Le pregunto a ellos si también cumplen la regla
    return btree_es_estricto(arbol->izq) && btree_es_estricto(arbol->der);
}

int btree_es_lista(BTree arbol){
  if(btree_empty(arbol)) return 1;

  //si tnego 2 hijos...
  if(!btree_empty(arbol->izq)&&!btree_empty(arbol->der)) return 0;

  return btree_es_lista(arbol->izq) && btree_es_lista(arbol->der);
}

void * btree_maximo(BTree arbol, FuncionComparadora comp){
  if(empty(arbol)) return NULL;

  void * dato_izq = btree_maximo(arbol->izq,comp);
  void * dato_der = btree_maximo(arbol->der,comp);

  void * max=arbol->dato;

  if (dato_izq != NULL && comp(max, dato_izq) < 0) {
        max = dato_izq;
    }

    if (dato_der != NULL && comp(max, dato_der) < 0) {
        max = dato_der;
    }
  
  return max;
  

}


BTree btree_espejo(BTree arbol, FuncionCopia copy){
  if(btree_empty(arbol)) return NULL;

  return btree_unir(arbol->dato,btree_espejo(arbol->der,copy),btree_espejo(arbol->izq,copy),copy);
}

int btree_contar_apariciones(BTree arbol, void * dato_buscado, FuncionComparadora comp){
  if(btree_empty(arbol)) return 0;

  if(comp(arbol->dato,dato_buscado)==0) return 1 + btree_contar_apariciones(arbol->izq,dato_buscado,comp) + btree_contar_apariciones(arbol->der,dato_buscado,comp);
  else return btree_contar_apariciones(arbol->izq,dato_buscado,comp) + btree_contar_apariciones(arbol->der,dato_buscado,comp);
}

BTree btree_podar_hojas(BTree arbol, FuncionDestructora destroy){
  if(btree_empty(arbol)) return arbol; //no tengo hojas.

  //si soy hoja..me podo:
  if(btree_empty(arbol->izq)&&btree_empty(arbol->der)){
    destroy(arbol->dato);
    free(arbol);
    return NULL;
  }

  arbol->izq=btree_podar_hojas(arbol->izq,destroy) ;
  arbol->der=btree_podar_hojas(arbol->der,destroy);

  return arbol;
}

BTree btree_mapear(BTree arbol, FuncionTransformadora transformar){
  if(btree_empty(arbol)) return NULL;

  return btree_unir(arbol->dato,btree_mapear(arbol->izq,transformar),btree_mapear(arbol->der,transformar),transformar);
}

