#include "slist_alternativa.h"
#include <stdlib.h>


SList slist_crear() {
    SList creada = malloc(sizeof(SListEstructura));

    if (creada == NULL) return NULL;

    creada->primero=NULL;
    creada->ultimo=NULL;

    return creada;
}

void slist_destruir(SList lista) {
    SNodo *actual = lista->primero;
    SNodo *siguiente;

    while (actual != NULL) {
        siguiente = actual->sig;
        free(actual);
        actual=siguiente;
    }
  
    free(lista);
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
    if (lista == NULL) return NULL;

    SNodo *nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = NULL;

    if (lista->primero == NULL){
        lista->primero=nuevoNodo;
        lista->ultimo=nuevoNodo;
    }else{

        lista->ultimo->sig=nuevoNodo;
        lista->ultimo = nuevoNodo;
    }

    return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
    if (lista == NULL) return NULL;

    SNodo *nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista->primero;


    lista->primero=nuevoNodo;
    if(lista->ultimo==NULL) lista->ultimo=nuevoNodo;

    return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
    SNodo * tmp;
    for(tmp=lista->primero;tmp!=NULL;tmp=tmp->sig){
        visit(tmp->dato);
    }
}

int slist_longitud(SList lista){
    if (lista == NULL) return 0;

    int contador=0;

    SNodo * tmp = lista->primero;
    while(tmp!=NULL){
        contador++;
        tmp=tmp->sig;
    }
    return contador;
}


SList slist_concatenar(SList lista1, SList lista2){
  if(lista1==NULL || lista1->primero == NULL) {
    lista1=lista2;
    return lista1;
  }

  if(lista2==NULL ||lista2->primero == NULL) return lista1;

  lista1->ultimo->sig = lista2->primero;

  lista1->ultimo=lista2->ultimo;

  return lista1;
}

SList slist_insertar(SList lista,int dato, int pos){
    if (pos == 0) {
        return slist_agregar_inicio(lista, dato);
    }

    SNodo *temp = lista->primero;
    int i = 0;
    
    // Caminamos hasta el nodo ANTERIOR a la posición deseada
    while(temp != NULL && i < pos - 1){
        temp = temp->sig;
        i++;
    }

    // Si llegamos a una posición válida
    if (temp != NULL) {
        SNodo *nuevoNodo = malloc(sizeof(SNodo)); // Pedimos la memoria
        nuevoNodo->dato = dato;
        
        // 1. El nuevo nodo atrapa la cola de la lista
        nuevoNodo->sig = temp->sig; 
        
        // 2. El nodo anterior suelta la cola y se agarra al nuevo nodo
        temp->sig = nuevoNodo;      
    }
    
    return lista;
}

SList slist_eliminar(SList lista, int pos){
  if (lista == NULL || lista->primero == NULL) return NULL; 

    // Caso especial: Borrar el primer elemento
    if (pos == 0) {
        SNodo *nodoAEliminar = lista->primero;
        lista->primero = lista->primero->sig; 

        // Si la lista quedó vacía al borrar el único elemento...
        if (lista->primero == NULL) {
            lista->ultimo = NULL;
        }

        free(nodoAEliminar);
        return lista;
    }

    SNodo *temp = lista->primero;
    int i = 0;
    
    // Caminamos hasta el nodo ANTERIOR al que queremos borrar
    // Verificamos que temp->sig no sea NULL para asegurarnos de que el nodo a borrar existe
    while(temp != NULL && temp->sig != NULL && i < pos - 1){
        temp = temp->sig;
        i++;
    }

    // Si el nodo anterior existe y el que queremos borrar también
    if (temp != NULL && temp->sig != NULL) {
        SNodo *nodoAEliminar = temp->sig;
        
        // Hacemos el puente: el nodo actual se salta al nodo a eliminar
        temp->sig = nodoAEliminar->sig; 

        if (nodoAEliminar == lista->ultimo) {
            lista->ultimo = temp;
        }
        
        // Destruimos el nodo desconectado
        free(nodoAEliminar);
    }
    
    return lista;
}


int slist_contiene(SList lista, int dato){
  SNodo * tmp;
  for(tmp=lista->primero;tmp!=NULL;tmp=tmp->sig){
      if(tmp->dato==dato) return 1;
  }
  return -1;
}

int slist_indice(SList lista,int dato){
  SNodo * tmp;
  int x=0;
  for(tmp=lista->primero;tmp!=NULL;tmp=tmp->sig){
      if(tmp->dato==dato) return x;
      x++;
  }
  return -1;
}

SList slist_intersecar(SList lista1, SList lista2){
  SList  lista=slist_crear();

  SNodo * temp;
  for(temp=lista1->primero;temp!=NULL;temp=temp->sig){
    for(SNodo * tmp=lista2->primero;tmp!=NULL;tmp=tmp->sig){
      if(temp->dato==tmp->dato){
        lista=slist_agregar_final(lista,temp->dato);
      }
    }
  }

  return lista;

}

SList slist_intersecar_v_opt(SList lista1, SList lista2){
  SNodo * lista_resultado = slist_crear();
  SNodo * temp;
  
  for(temp = lista1->primero; temp != NULL; temp = temp->sig){
      
      // Si el elemento actual de lista1 también ESTÁ en lista2...
      if(slist_contiene(lista2, temp->dato) == 1){
          
          lista_resultado = slist_agregar_final(lista_resultado, temp->dato);
      }
  }

  return lista_resultado;
}

SList slist_intersercar_custom(SList lista1, SList lista2,FuncionComparadora fun){
  SNodo * lista=slist_crear();

  SNodo * temp;
  SNodo * tmp;
  for(temp=lista1->primero;temp!=NULL;temp=temp->sig){
    for( tmp=lista2->primero;tmp!=NULL;tmp=tmp->sig){
      if(fun(temp->dato,tmp->dato)){
        lista=slist_agregar_final(lista,temp->dato);
      }
    }
  }

  return lista;

}


SList slist_ordenar(SList lista,FuncionComparadora fun){
  if(lista == NULL) return NULL;
  
  int hubo_cambio = 1;
  while(hubo_cambio){
    hubo_cambio = 0;
    
    // Recorremos hasta el anteúltimo nodo
    for(SNodo * tmp = lista->primero; tmp->sig != NULL; tmp = tmp->sig){
        
        // Si la función dice que el actual es MAYOR (> 0) que el siguiente...
        if(fun(tmp->dato, tmp->sig->dato) > 0){
            // Intercambiamos los DATOS
            int aux = tmp->dato;
            tmp->dato = tmp->sig->dato;
            tmp->sig->dato = aux;
            
            hubo_cambio = 1; // Marcamos que hubo un cambio para volver a revisar
        }
    }
  }
  return lista;
}


//si tenemos 1 2 3 , y hacemos agregar inicio(1), agregar inicio(2) -> 2 1
SList slist_reverso(SList lista){
  SList lista_reversa=slist_crear();

  SNodo * tmp;
  for(tmp=lista->primero;tmp!=NULL;tmp=tmp->sig){
      lista_reversa=slist_agregar_inicio(lista_reversa,tmp->dato);
  }
  
  return lista_reversa;
}


SList slist_intercalar(SList lista1, SList lista2){
  SList lista=slist_crear();
  if(lista1->primero==NULL) {
    lista=lista2->primero;
    return lista;
  }
  if(lista2->primero==NULL) {
    lista=lista1->primero;
    return lista;
  }

  SNodo * tmp1=lista1->primero;
  SNodo * tmp2=lista1->primero;

  while(tmp1 != NULL || tmp2 != NULL){
    
    if(tmp1 != NULL){
      lista = slist_agregar_final(lista, tmp1->dato);
      tmp1 = tmp1->sig; // Avanzamos solo en la lista 1
    }
    
    if(tmp2 != NULL){
      lista = slist_agregar_final(lista, tmp2->dato);
      tmp2 = tmp2->sig; // Avanzamos solo en la lista 2
    }
  }

  return lista;
}


SList slist_partir(SList lista){
  if(lista==NULL|| lista->primero == NULL || lista->primero == lista->ultimo) return NULL;
  int longitud=slist_longitud(lista);
  if(longitud == 1) return NULL;

  //int punto_corte = (longitud % 2 == 0) ? (longitud / 2) : (longitud / 2) + 1;


  if(longitud%2==0){
    SNodo * tmp;
    int contador=0;
    tmp=lista->primero;
    while(tmp!=NULL && contador<(longitud/2)-1){
      contador++;
      tmp=tmp->sig;
    }
    SList segunda_mitad = slist_crear();
    segunda_mitad->primero = tmp->sig;
    segunda_mitad->ultimo = lista->ultimo;
    // ¡CORTAMOS LA LISTA ORIGINAL!
    tmp->sig = NULL;
    lista->ultimo = tmp;
    return  segunda_mitad;
  }else{
    SNodo * tmp;
    int contador=0;
    tmp=lista->primero;
    while(tmp!=NULL && contador<(longitud/2 +1)-1){
      contador++;
      tmp=tmp->sig;
    }
    SList segunda_mitad = slist_crear();
    segunda_mitad->primero = tmp->sig;
    segunda_mitad->ultimo = lista->ultimo;
    // ¡CORTAMOS LA LISTA ORIGINAL!
    tmp->sig = NULL;
    lista->ultimo = tmp;
    return  segunda_mitad;
  }
}

/*

Todas estas operaciones dependen del tamaño de sus argumentos (N)! 
slist_ordenar: Esta es indiscutiblemente la que más tiempo consume. 
Al usar un Bubble Sort, su complejidad es O(N^2) en el peor de los casos (lista invertida). 
Si le pasas una lista muy larga, el tiempo de ejecución se dispara exponencialmente.

slist_intercalar: Depende linealmente del tamaño de la suma de ambas listas. 
Su complejidad es O(N + M).

slist_reverso: Tiene una trampa. Nuestro for es O(N), pero como llama a slist_agregar_inicio (que es instantánea, O(1)), 
su tiempo total es lineal: O(N).

slist_partir: Primero recorre la lista completa para sacar la longitud O(N), y luego recorre hasta la mitad O(N/2). Termina siendo lineal O(N).

*/