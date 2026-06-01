#include <stdio.h>
#include <stdlib.h>
//#include "../Practica_3/Cola/cola.h"

typedef void (*FuncionVisitante)(void * dato);
typedef void (*FuncionDestructora)(void * dato);
typedef void * (*FuncionCopia)(void * dato);
typedef void (*FuncionVisitanteExtra) (void * dato, void *extra);
typedef int (*FuncionComparadora) (void *a , void * b);

typedef enum {
  BTREE_RECORRIDO_IN, //Subàrbol izquierdo - procesar la raìz - subàrbol derecho
  BTREE_RECORRIDO_PRE,//Procesar la raìz - subàrbol izquierdo - subàrbol derecho
  BTREE_RECORRIDO_POST//ubàrbol izquierdo - subàrbol derecho - procesar la raìz
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo{
    void * dato;
    struct _BTNodo *izq;
    struct _BTNodo *der;
} *BTree;

int btree_empty(BTree nodo) {
    return nodo == NULL; 
}

int btree_son_iguales(BTree arbol1, BTree arbol2, FuncionComparadora comp){

  if(btree_empty(arbol1) && btree_empty(arbol2)) return 1;

  if(btree_empty(arbol2)|| btree_empty(arbol1) ) return 0;

  if(comp(arbol1->dato,arbol2->dato)!=0 ) return 0;

  
  return btree_son_iguales(arbol1->izq,arbol2->izq,comp) && btree_son_iguales(arbol1->der, arbol2->der, comp);

  return 0;
}


int btree_contar_hojas(BTree arbol){
  if(btree_empty(arbol)) return 0;

  //soy una hoja
  if(btree_empty(arbol->izq) && btree_empty(arbol->der) )return 1 ;

  return  btree_contar_hojas(arbol->izq) + btree_contar_hojas(arbol->der);
}

void * copiar_puntero_btree(void * nodo) {
    return nodo; 
}

void no_destruir_nada(void * nodo) {
    // nada
}
/*
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
        BTree actual = (BTree)sala_espera->inicio;
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
}*/

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


int btree_nnodos(BTree arbol){
  if (btree_empty(arbol)) return 0;

  return 1 + btree_nnodos(arbol->der) + btree_nnodos(arbol->izq);
  
}

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





void btree_destruir(BTree nodo,FuncionDestructora destroy) {
  if (nodo != NULL) {
    btree_destruir(nodo->izq,destroy);
    btree_destruir(nodo->der,destroy);
    destroy(nodo->dato);
    free(nodo);
  }
}


BTree btree_crear() {
   return NULL;
}

BTree btree_unir(void * dato, BTree left, BTree right, FuncionCopia copy) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  if(nuevoNodo!=NULL){
    nuevoNodo->dato = copy(dato);
    nuevoNodo->izq = left;
    nuevoNodo->der = right;
  }
  return nuevoNodo;
}

//--------------
int * copiar_entero(int * entero){
    int * a = malloc(sizeof(int));
    *a=*entero;
    return a;
}

void imprimir_enteros(int * entero){
    printf("%d -",*entero);
}

void sumar_enteros_extra(int * dato, int * acumulador){
    *acumulador= *acumulador + *dato;
}

int comparar_enteros(int * a, int * b){
    if(*a>*b) return 1;
    if(*a<*b) return -1;
    return 0;
}

void destruir_enteros(int * a){
    free(a);
}

int main(void ){
    printf("creando arbol de prueba...\n");
    int val1 = 68, val2 = 6, val3 = 60, val4 = 683;
    BTree prueba1 = btree_unir(&val1, NULL, NULL, (FuncionCopia)copiar_entero);
    BTree prueba2=btree_unir(&val2,NULL,NULL,(FuncionCopia)copiar_entero);
    BTree nodo=btree_unir(&val3,prueba1,prueba2,(FuncionCopia)copiar_entero);
    BTree nodo2=btree_unir(&val4,nodo,NULL,(FuncionCopia)copiar_entero);
    
    printf("Probando funciones...\n");
    int r1=btree_son_iguales(prueba1,nodo2,(FuncionComparadora)comparar_enteros);
    printf("son iguales?: %s", r1==1 ? "si": "no");
    int r2=btree_contar_hojas(nodo2);
    printf("hojas: %d\n",r2);
    int r3=btree_altura(nodo2);
    printf("altura: %d\n",r3);
    int r4=btree_nnodos_profundidad(nodo2,2);
    printf("cant de nodos en la profundidad 2: %d\n",r4);
    int r5=btree_nnodos(nodo2);
    printf("numero nodos: %d\n",r5);
    int r6=btree_empty(prueba2);
    printf("es vacio?: %s\n",r6==1 ? "si": "no");

    printf("recorrer IN ORDER...\n");
    btree_recorrer(nodo2,BTREE_RECORRIDO_IN,(FuncionVisitante)imprimir_enteros);
    printf("recorrer bfs...\n");
    //btree_recorrer_bfs(nodo2,(FuncionVisitante)imprimir_enteros);
    printf("recorrer extra EN POST...\n");
    int suma=0;
    btree_recorrer_extra(nodo2,BTREE_RECORRIDO_POST,(FuncionVisitanteExtra)sumar_enteros_extra,&suma);
    printf("la suma es: %d\n",suma);

    btree_destruir(nodo2,(FuncionDestructora)destruir_enteros);

    printf("\nMemoria liberada. Fin del programa.\n");
    
    return 0;
}