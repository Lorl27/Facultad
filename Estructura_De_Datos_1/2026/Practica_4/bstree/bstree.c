#include "bstree.h"
#include <assert.h>
#include <stdlib.h>



/**
 * bstee_crear: Retorna un arbol de busqueda binaria vacio
 */
BSTree bstee_crear() {
   return NULL; 
}


BSTree bstree_empty(BSTree arbol){
    return arbol==NULL;
}


void bstree_destruir(BSTree raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    bstree_destruir(raiz->izq, destr);
    bstree_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
};


int bstree_buscar(BSTree raiz, void *dato, FuncionComparadora comp) {
  if (raiz == NULL) return 0;

  if (comp(dato, raiz->dato) == 0) return 1;

  else if (comp(dato, raiz->dato) < 0) return bstree_buscar(raiz->izq, dato, comp);
  
  else return bstree_buscar(raiz->der, dato, comp);
}



BSTree bstree_insertar(BSTree arbol, void *dato, FuncionCopiadora copy,FuncionComparadora comp) {
  if(btree_empty(arbol)){
        BSTree nuevo=malloc(sizeof (struct _BST_Nodo));
        nuevo->dato=copy(dato);
        nuevo->der=NULL;
        nuevo->izq=NULL;
        return nuevo;
    }

    int busqueda=comp(arbol->dato,dato);

    if(busqueda<0) arbol->der= bstree_insertar(arbol->der,dato,comp,copy);
    else if(busqueda>0) arbol->izq= bstree_insertar(arbol->izq,dato,comp,copy);

    return arbol;
}


void bstree_recorrer(BSTree raiz, BSTreeRecorrido orden,FuncionVisitanteExtra visita, void *extra) {
  if (raiz != NULL) {

    if (orden == BTREE_RECORRIDO_PRE) visita(raiz->dato, extra);
    bstree_recorrer(raiz->izq, orden, visita, extra);

    if (orden == BTREE_RECORRIDO_IN) visita(raiz->dato, extra);
    bstree_recorrer(raiz->der, orden, visita, extra);

    if (orden == BTREE_RECORRIDO_POST)visita(raiz->dato, extra);
  }
}

BSTree btree_search(BSTree arbol, void * elemento, FuncionComparadora comp){
    if(btree_empty(arbol)) return NULL;

    int busqueda=comp(arbol->dato,elemento);
    if(busqueda==0) return arbol;
    else if(busqueda<0) return btree_search(arbol->izq,elemento,comp);
    else if(busqueda>0) return btree_search(arbol->der,elemento,comp);

    return NULL;
    
}


BSTree bstree_eliminar(BSTree arbol, void *dato,FuncionComparadora comp, FuncionDestructora destroy){
  if(bstree_empty(arbol)) return arbol;

  //Primero hay que buscar el dato!
  int comparacion=comp(arbol->dato,dato);

  if(comparacion<0) arbol->der=bstree_eliminar(arbol->der,dato,comp,destroy);
  else if(comparacion>0) arbol->izq=bstree_eliminar(arbol->izq,dato,comp,destroy);


  //si lo encontramos...
  else if(comparacion==0){
    //si es una hoja...
    if(bstree_empty(arbol->der)&&bstree_empty(arbol->izq)){
      destroy(arbol->dato);
      free(arbol);
      return NULL;
    }

    //si tiene un solo hijo...
    else if (!bstree_empty(arbol->der) || !bstree_empty(arbol->izq)){
      if(!bstree_empty(arbol->izq)){ //significa que mi hijo esta aca
        BSTree tmp = arbol->izq;
        destroy(arbol->dato);
        free(arbol);
        return tmp;
      }

      //si no, esta en el derecho:
      if(!bstree_empty(arbol->der)){ //significa que mi hijo esta aca
        BSTree tmp = arbol->der;
        destroy(arbol->dato);
        free(arbol);
        return tmp;
      }
    }

    //si tiene 2 hojas.. debemos hallar dònde reubicar.
    // Buscamos el sucesor (el nodo más a la izquierda del subárbol derecho) (MÍNIMO del subárbol DERECHO)
    BSTree sucesor = arbol->der;
     while (sucesor->izq != NULL) {
       sucesor = sucesor->izq;
    }

    // Intercambiamos los datos para que nuestro nodo tenga el dato vàlido
    void * dato_basura = arbol->dato;
    arbol->dato = sucesor->dato;
    sucesor->dato = dato_basura;

     arbol->der = bstree_eliminar(arbol->der, dato_basura, comp, destroy);

  }

  return arbol;

}

int bstree_nnodos(BSTree arbol){
    if(bstree_empty(arbol)) return 0;

    return 1 + bstree_nnodos(arbol->izq) + bstree_nnodos(arbol->der);
}


void * bstree_k_esimo_menor_aux(BSTree arbol, int * k) {
    if (bstree_empty(arbol)) return NULL;

    //  Buscamos en los más chicos
    void * resultado_izq = bstree_k_esimo_menor_aux(arbol->izq, k);
    
    if (resultado_izq != NULL) return resultado_izq;
    
    
    (*k)--;
    
    // soy yo!
    if (*k == 0) return arbol->dato;
    

    // sigo buscando en los más grandes
    return bstree_k_esimo_menor_aux(arbol->der, k);
}

void * bstree_k_esimo_menor(BSTree arbol, int k){
  if( k<=0) return NULL;
  
  return bstree_k_esimo_menor_aux(arbol, &k);
}

/* Una forma màs òptimizada es alterando la estrucuta para tener
struct _BST_Nodo {
  void *dato;
  int cant_izq; // Cantidad de nodos que hay en su rama izquierda
  struct _BST_Nodo *izq;
  struct _BST_Nodo *der;
};

y con ello:
- si k=cant_izq+1 --> llegamos!
- si k<=cant_izq -> buscamos por izq
- si k>cant_izq+1 --> buscamos por der
*/

int bstree_validar_aux(BSTree arbol, void ** prev, FuncionComparadora comp) {
    if (bstree_empty(arbol)) return 1; 

    if (bstree_validar_aux(arbol->izq, prev, comp) == 0) return 0;

    if (*prev != NULL && comp(arbol->dato, *prev) <= 0) return 0; 
    
    *prev = arbol->dato;

    return bstree_validar_aux(arbol->der, prev, comp);
}

int bstree_validar(BSTree arbol, FuncionComparadora comp) {
    void * dato_prev = NULL; // Al principio no hemos visitado a nadie
    
    return bstree_validar_aux(arbol, &dato_prev, comp);
}

void bstree_imprimir_rango(BSTree arbol, void * min, void * max, FuncionComparadora comp, FuncionVisitante imprimir){
  if(bstree_empty(arbol)) return;


  if(comp(arbol->dato,min)>0) bstree_imprimir_rango(arbol->izq,min,max,comp,imprimir);

  if(comp(arbol->dato,min)>=0 && comp(arbol->dato,max)<=0){
    imprimir(arbol->dato);
  }
  
  if(comp(arbol->dato,max)<0)bstree_imprimir_rango(arbol->der,min,max,comp,imprimir);

  
}

void * bstree_ancentro_comun(BSTree arbol, void * dato1, void* dato2, FuncionComparadora comp){
  if(bstree_empty(arbol)) return NULL;

  //si los datos son menores que mi raìz ... entonces busco en la izquierda
  if(comp(arbol->dato,dato1)>0 && comp(arbol->dato,dato2)>0) return bstree_ancentro_comun(arbol->izq,dato1,dato2,comp);

  //si uno es menor y el otro mayor, soy el que busco!
  if(comp(arbol->dato,dato1)>=0 && comp(arbol->dato,dato2)<=0 || comp(arbol->dato,dato1)<=0 && comp(arbol->dato,dato2)>=0 ) return arbol->dato;

  //si los datos son mayores que mi raiz.... busco en la derecha
  return bstree_ancentro_comun(arbol->der,dato1,dato2,comp);
}

void * bstree_techo_aux(BSTree arbol, void ** encontrado,void * objetivo, FuncionComparadora comp){
  if(bstree_empty(arbol)) return *encontrado;

  if(comp(arbol->dato,objetivo)>0){
    *encontrado=arbol->dato;
    return bstree_techo_aux(arbol->izq,encontrado,objetivo,comp);
  }

  if(comp(arbol->dato,objetivo)<0){
    return bstree_techo_aux(arbol->der,encontrado,objetivo,comp);
  }

  if(comp(arbol->dato,objetivo)==0) *encontrado=arbol->dato;
    

  return *encontrado;
}


void * bstree_techo(BSTree arbol, void * objetivo, FuncionComparadora comp){
  
  void * encontrado=NULL;

  return bstree_techo_aux(arbol,&encontrado,objetivo,comp);
}


void * bstree_techo_directo(BSTree arbol, void * objetivo, FuncionComparadora comp) {
    if (arbol == NULL) return NULL;

    int comparacion = comp(arbol->dato, objetivo);

    // Si soy igual, soy la respuesta.
    if (comparacion == 0) return arbol->dato;

    // Si soy menor, la respuesta SI O SI está a mi derecha (o no existe)
    if (comparacion < 0) return bstree_techo_directo(arbol->der, objetivo, comp);

    // Si soy mayor, soy un candidato...
    // Pero primero mando a revisar si hay alguien mejor en mi rama izquierda.
    void * techo_izquierdo = bstree_techo_directo(arbol->izq, objetivo, comp);
    
    // Si la izquierda encontró un techo mejor, devuelvo ese.
    if (techo_izquierdo != NULL) return techo_izquierdo;
    
    // Si la izquierda devolvió NULL (no había nadie mejor), ¡entonces el techo soy yo!
    return arbol->dato;
}


void * bstree_minimo_iterativo(BSTree arbol){
  if(bstree_empty(arbol)) return NULL;

  BSTree arbol_izq=arbol->izq;
  while(arbol_izq!=NULL){
    arbol_izq=arbol_izq->izq;
  }

  return arbol_izq->dato;

}


int bstree_contar_mayores(BSTree arbol, void * limite, FuncionComparadora comp){
  if(bstree_empty(arbol)) return 0;

  int comparacion=comp(arbol->dato,limite);

  if(comparacion>0) return bstree_contar_mayores (arbol->izq,limite,comp) + bstree_contar_mayores (arbol->der,limite,comp) + 1;

  return bstree_contar_mayores(arbol->der,limite,comp); 
}

BSTree bstree_clonar_si_aux(BSTree origen,BSTree nuevo, Predicado cumple_condicion, FuncionCopiadora copy, FuncionComparadora comp){
  if(bstree_empty(origen)) return nuevo;

  if(cumple_condicion(origen->dato)) nuevo=bstree_insertar(nuevo,origen->dato,copy,comp);

  nuevo=bstree_clonar_si_aux(origen->izq,nuevo,cumple_condicion,copy,comp);
  nuevo=bstree_clonar_si_aux(origen->der,nuevo,cumple_condicion,copy,comp);

  return nuevo;
}

BSTree bstree_clonar_si(BSTree origen, Predicado cumple_condicion, FuncionCopiadora copy, FuncionComparadora comp){
  
  BSTree nuevo=bstee_crear();

  return bstree_clonar_si_aux(origen,nuevo,cumple_condicion,copy,comp);
}


int bstree_validar_camino(BSTree arbol, void ** camino, int longitud_camino, FuncionComparadora comp){
  // Si ya no quedan elementos en el arreglo para revisar, ¡el camino fue válido!
    if (longitud_camino == 0) return 1;

    // Si el árbol se acabó pero aún nos quedan elementos en el arreglo, es inválido
    if (arbol == NULL) return 0;

    // El nodo actual DEBE coincidir con el elemento actual del arreglo (camino[0])
    if (comp(arbol->dato, camino[0]) != 0) return 0;

    // Si coinciden, miramos el siguiente elemento del arreglo para decidir hacia dónde bajar
    if (longitud_camino > 1) {
        int comparacion = comp(camino[1], arbol->dato); // Comparamos el siguiente paso con mi raíz
        
        // "camino + 1" avanza el puntero del arreglo a la siguiente posición
        if (comparacion > 0) return bstree_validar_camino(arbol->der, camino + 1, longitud_camino - 1, comp);
        else return bstree_validar_camino(arbol->izq, camino + 1, longitud_camino - 1, comp);
    }

    return 1; // Si coincidió y era el último elemento, es válido.

}