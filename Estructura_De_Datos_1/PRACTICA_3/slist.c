#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitanteEntero visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

//-----

int slist_longitud(SList lista){
    int cont=0;

    if(lista==NULL){
        printf("Lista vacía\n");
        return 0;
    }

    for(SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
        cont++;
    }

    return cont;
}

void slist_concatenar(SList l1, SList l2){

     for(SNodo *nodo = l2; nodo != NULL; nodo = nodo->sig){
        // printf("%d",nodo->dato);
        slist_agregar_final(l1,nodo->dato);

    }
}

SList slist_insertar(SList lista,int dato,int pos){
    SNodo *tmp = malloc(sizeof(SNodo));
    SNodo *newN = malloc(sizeof(SNodo));
    
    int contador=0;

    for(SNodo *nodo =lista; nodo!=NULL; nodo=nodo->sig){
        
        if(contador==pos){
            tmp=nodo->sig;
            nodo->sig=newN;
            newN->dato=dato;
            newN->sig=tmp;
        }

        contador++;
        
    }

    return lista;
}

SList slist_eliminar(SList lista, int pos){
    

    if (lista == NULL || pos <0) return NULL;
        
    if(pos==0){ //tengo q mover + destruir + dup2
        SNodo *tmp=lista;
        lista=lista->sig; //muevo inicio
        free(tmp);
        return lista;
    }
        
    int contador=0;

    for(SNodo *nodo=lista;nodo!=NULL;nodo=nodo->sig){
        if(contador==pos-1 && nodo->sig!=NULL){
            SNodo *aEliminar = nodo->sig;
            nodo->sig=nodo->sig->sig;
            free(aEliminar);
            break;
        }

        contador++;
        
    }

    return lista;
}


SList slist_borrar_dato(SList lista,int dato){
    if(lista==NULL) return NULL;

    if(lista->dato==dato){
        SNodo *aEliminar = lista;
        lista = lista->sig;
        free(aEliminar);
        return lista;
    }

    lista->sig=slist_borrar_dato(lista->sig,dato);

    return lista;
}

int slist_contiene(SList lista, int dato){
    if(lista==NULL) return -1;

    if(lista->dato==dato){
        return 0;
    }

    for(SNodo *nodo=lista;nodo!=NULL;nodo=nodo->sig){
        if(nodo->dato==dato){
            return 0;  // I found
        }
    }

    return 1; //no está
}

int slist_indice(SList lista, int elemento){
    if(lista==NULL) return -1;

    if(lista->dato==elemento) return 0;  //indice 0 ;)

    int indice=0;

    for(SNodo *nodo=lista; nodo!=NULL;nodo=nodo->sig){
        
        if(nodo->dato==elemento){
            return indice;
        }
        indice++;
    }

    return -1;
}

SList slist_intersecar(SList lista1, SList lista2) {
    if(lista1 == NULL || lista2 == NULL) return NULL;

    SList comunes = slist_crear();
    SNodo* temp1, *temp2;
    for(temp1 = lista1; temp1 != NULL; temp1 = temp1 -> sig) {
        int encontrado = 0;

        for(temp2 = lista2; temp2 != NULL && encontrado != 1; temp2 = temp2 -> sig) {
            if(temp1->dato == temp2->dato) {
                encontrado = 1;
            }
        }

        if(encontrado == 1) {
            comunes = slist_agregar_inicio(comunes, temp1->dato);
        }
    }

    return comunes;
}

SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparadoraEntero comp){
    if(lista1==NULL || lista2==NULL) return NULL;

    SList inter=slist_crear();

    SNodo* nodo1, *nodo2;

    for(nodo1=lista1;nodo1!=NULL;nodo1=nodo1->sig){
        int encontrado=0;
        for(nodo2=lista2;nodo2!=NULL && encontrado!=1;nodo2=nodo2->sig){
            if(comp(nodo1->dato,nodo2->dato)){
                encontrado=1;
            }
        }
        if(encontrado==1){
            inter=slist_agregar_inicio(inter,nodo1->dato);
        }
    }

    return inter;
}


SList slist_ordenar(SList lista, FuncionComparadoraEntero comp){
    if(lista==NULL || lista->sig ==NULL) return NULL;

    for(SNodo *nodo=lista;nodo!=NULL;nodo=nodo->sig){
        for(SNodo *nodo2=lista;nodo2->sig!=NULL;nodo2=nodo2->sig){
            if(comp(nodo2->dato,nodo2->sig->dato)>0){
                int tmp=nodo2->dato;
                nodo2->dato=nodo2->sig->dato;
                nodo2->sig->dato=tmp;
            }
        }
    }

    return lista;
}

SList slist_reverso(SList lista){
    if(lista==NULL || lista->sig==NULL) return lista;

    for(SNodo *n1=lista;n1!=NULL;n1=n1->sig){
        for(SNodo *n2=lista;n2->sig!=NULL;n2=n2->sig){
            if(n2->dato<n2->sig->dato){
                int tmp=n2->dato;
                n2->dato=n2->sig->dato;
                n2->sig->dato=tmp;
            }
        }
    }

    return lista;
}

SList slist_intercalar(SList lista1, SList lista2){
    if(lista1==NULL || lista2==NULL) return NULL;

    SList tmp=slist_crear();
    SNodo *nodo1=lista1;
    SNodo *nodo2=lista2;

    while(nodo1!=NULL || nodo2!=NULL){
        if(nodo1!=NULL){
            tmp=slist_agregar_final(tmp,nodo1->dato);
            nodo1=nodo1->sig;
        }

        if(nodo2!=NULL){
            tmp=slist_agregar_final(tmp,nodo2->dato);
            nodo2=nodo2->sig;
        }
    }

    return tmp;

}


SList slist_partir(SList lista){
    if(lista==NULL  || lista->sig==NULL) return NULL;

    int longitud=slist_longitud(lista);
    int medio=longitud/2;

    SList nodo=lista;
    for(int x=0;x<medio-1;x++){
        nodo=nodo->sig;
    }
    
    if(longitud%2==0) nodo=nodo->sig;  //primera lista: n+1

    SList mitad2=nodo->sig;
    nodo->sig=NULL;

    return mitad2;
}



/* PREGUNTA: 
* Indique cu´ales son las operaciones que piensa que m´as tiempo consumen en ejecutarse. 
* ¿Cu´ales de ellas dependen del tama˜no de sus argumentos?
* 
* Las que más tiempo consumirán son las que deben recorrer toda la lista como por ej, agregrar_final ya que van a depender del tamaño de la misma.
*
*/

