#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

void  destruir(void * dato){
  free(dato);
}

void * copiar(void * dato){
  int * copy=malloc(sizeof(int));
  *copy=*(int*)dato;
  return copy;
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear(),copiar);
  BTree l = btree_unir(2, ll, btree_crear(),copiar);
  BTree r = btree_unir(3, btree_crear(), btree_crear(),copiar);
  BTree raiz = btree_unir(4, l, r,copiar);

  btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");
  btree_recorrer(raiz, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");
  btree_destruir(raiz,destruir);

  return 0;
}
