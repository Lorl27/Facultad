#include "avl.h"
#include <stdio.h>
#include <stdlib.h>


AVL avl_crear() {
  AVL arbol = malloc(sizeof(struct _AVL_Nodo));
  if(!avl_empty(arbol)){
    arbol->der=NULL;
    arbol->izq=NULL;
    arbol->altura=-1;
  }
  return arbol;
}

int avl_empty(AVL arbol){
  return arbol == NULL;
}


void avl_destruir(AVL arbol, FuncionDestructora destroy) {
  if(!avl_empty(arbol)){
    // destruir los nodos en postorder
    avl_destruir(arbol->izq, destroy);
    avl_destruir(arbol->der, destroy);
    destroy(arbol->dato);
    free(arbol);
  }
}


int avl_buscar(AVL arbol, void* dato, FuncionComparadora comp) {
  if(avl_empty(arbol)) return 0;

  int comparacion=comp(arbol->dato,dato);

  if(comparacion<0) return avl_buscar(arbol->izq,dato,comp);
  if(comparacion==0) return 1;
  
  return avl_buscar(arbol->der,dato,comp);

}


int avl_altura_arbol(AVL arbol) {
  return avl_empty(arbol) ? -1 : arbol->altura;
}

int avl_altura_max_hijos(AVL arbol){
  if(avl_empty(arbol)) return -1;

  int altura_izq=avl_altura_arbol(arbol->izq);
  int altura_der=avl_altura_arbol(arbol->der);

  if (altura_der>altura_izq) return altura_der;
  return altura_izq;
}

int avl_factor_balance(AVL nodo){
  if(avl_empty(nodo)) return 0;
  return avl_altura_arbol(nodo->izq) - avl_altura_arbol(nodo->der);
}


AVL avl_rotacion_derecha(AVL arbol){
  if(avl_empty(arbol)) return NULL;

  AVL hijo_izquierdo=arbol->izq;
  AVL huerfano=hijo_izquierdo->der;

  arbol->izq=huerfano;
  hijo_izquierdo->der=arbol;

  arbol->altura= 1 + avl_altura_max_hijos(arbol);
  hijo_izquierdo->altura= 1 +  avl_altura_max_hijos(hijo_izquierdo);

  return hijo_izquierdo;
}

AVL avl_rotacion_izquierda(AVL arbol){
  if(avl_empty(arbol)) return NULL;

  AVL hijo_derecho=arbol->der;
  AVL huerfano=hijo_derecho->izq;

  arbol->der=huerfano;
  hijo_derecho->izq=arbol;

  arbol->altura= 1 + avl_altura_max_hijos(arbol);
  hijo_derecho->altura= 1 +  avl_altura_max_hijos(hijo_derecho);

  return hijo_derecho;
}


AVL avl_rebalancear(AVL arbol){
  //SI esta desbalanceado a la izquierda, rotamos a la derecha
  if(avl_factor_balance(arbol)>=2){

    //Si ademas, hijo izq pesa a la derecha, debemos hacer una rotacion doble (Izquierda-Derecha)
    if(avl_factor_balance(arbol->izq)<=-1){
      arbol->izq=avl_rotacion_izquierda(arbol->izq);
    }

    arbol=avl_rotacion_derecha(arbol);
  }

  //SI esta desbalanceado a la derecha, rotamos a la izquierda
  if(avl_factor_balance(arbol)<=-2){

    //Si ademas, hijo der pesa a la izquierda debemos hacer una rotacion antes (Derecha-Izquierda)
    if(avl_factor_balance(arbol->der)>=1){
      arbol->der=avl_rotacion_derecha(arbol->der);
    }

    arbol=avl_rotacion_izquierda(arbol);
  }


  return arbol;
}


AVL avl_insertar(AVL arbol, void * dato, FuncionCopiadora copy, FuncionComparadora comp){
  if(avl_empty(arbol)){
    AVL nuevo = malloc(sizeof(struct _AVL_Nodo));
    nuevo->altura=0; // es una hoja
    nuevo->dato=copy(dato);
    nuevo->der=NULL;
    nuevo->izq=NULL;
    return nuevo;
  }

  int comparacion=comp(arbol->dato,dato);
  if(comparacion>0) arbol->izq=avl_insertar(arbol->izq,dato,copy,comp);
  if(comparacion<0) arbol->der=avl_insertar(arbol->der,dato,copy,comp);
  if(comparacion==0) return arbol; //es repetido

  arbol->altura= 1 + avl_altura_max_hijos(arbol);
  return avl_rebalancear(arbol);
}


int avl_validar_que_es_abb_aux(AVL arbol , void ** dato_previo, FuncionComparadora comp){
  if(avl_empty(arbol)) return 1;

  if(avl_validar_que_es_abb_aux(arbol->izq,dato_previo,comp)==0) return 0;

  if(*dato_previo != NULL && comp(arbol->dato,*dato_previo)<=0) return 0;

  *dato_previo=arbol->dato;

  return avl_validar_que_es_abb_aux(arbol->der,dato_previo,comp);
}

int avl_validar_que_es_abb(AVL arbol, FuncionComparadora comp){
  void * dato_prev = NULL;
  return avl_validar_que_es_abb_aux(arbol,&dato_prev,comp);
}

int avl_validar_altura_y_balance(AVL arbol) {
  if(avl_empty(arbol)) return 1;

  int val_izq = avl_validar_altura_y_balance(arbol->izq);
  int val_der = avl_validar_altura_y_balance(arbol->der);

  if (val_izq && val_der) {
    // si ambos subarboles son validos, validar altura y balance de la raiz
    int altura = 1 + avl_altura_max_hijos(arbol);
    int balance = avl_factor_balance(arbol);
    if ((arbol->altura == altura) && (balance >= -1) && (balance <= 1)) return 1;
  }

  return 0;
}
int avl_validar(AVL arbol, FuncionComparadora comp) {
  return avl_validar_altura_y_balance(arbol) && avl_validar_que_es_abb(arbol, comp);
}


void avl_recorrer(AVL arbol, AVLRecorrido orden, FuncionVisitanteExtra visit, void * extra){
  if(avl_empty(arbol)) return;

  if(orden==AVL_RECORRIDO_PRE) visit(arbol->dato,extra);
  avl_recorrer(arbol->izq,orden,visit,extra);
  if(orden==AVL_RECORRIDO_IN) visit(arbol->dato,extra);
  avl_recorrer(arbol->der,orden,visit,extra);
  if(orden==AVL_RECORRIDO_POST) visit(arbol->dato,extra);

}

AVL eliminar_elemento(AVL arbol, void * elemento, FuncionComparadora comp, FuncionDestructora destroy){
  if(avl_empty(arbol)) return NULL;

  int comparacion=comp(arbol->dato,elemento);

  if(comparacion>0) arbol->izq= eliminar_elemento(arbol->izq,elemento,comp,destroy);
  if(comparacion<0) arbol->der= eliminar_elemento(arbol->der,elemento,comp,destroy);

  if(comparacion==0){
    
    //es una hoja
    if(avl_empty(arbol->der) && avl_empty(arbol->izq)){
      destroy(elemento);
      free(arbol);
      return NULL;
    }

    if(!avl_empty(arbol->der)){
      AVL tmp = arbol->der;
      destroy(arbol);
      free(arbol->dato);
      return tmp;
    }

    if(!avl_empty(arbol->izq)){
      AVL tmp = arbol->izq;
      destroy(arbol);
      free(arbol->dato);
      return tmp;
    }

    //si tiene 2 hojas.. debemos hallar dònde reubicar.
    // Buscamos el sucesor (el nodo más a la izquierda del subárbol derecho) (MÍNIMO del subárbol DERECHO)
    AVL sucesor = arbol->der;
     while (sucesor->izq != NULL) {
       sucesor = sucesor->izq;
    }

    // Intercambiamos los datos para que nuestro nodo tenga el dato vàlido
    void * dato_basura = arbol->dato;
    arbol->dato = sucesor->dato;
    sucesor->dato = dato_basura;

    arbol->der = eliminar_elemento(arbol->der, dato_basura, comp, destroy);

  }

  arbol->altura= 1 +avl_altura_max_hijos(arbol) ;

  return avl_rebalancear(arbol);
}


