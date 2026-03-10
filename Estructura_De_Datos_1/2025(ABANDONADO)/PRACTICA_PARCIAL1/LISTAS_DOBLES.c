typedef struct _DNodo{
    struct _DNodo *sig;
    struct _DNodo *ant;
    int dato;
}DNodo;

typedef struct 
{
   DNodo *primero;
   DNodo *ultimo;
} DList;

#include <stdio.h>
#include <stdlib.h>

DList agregar_inicio(DList lista, int elemento){
    DNodo *nuevo=malloc(sizeof(DNodo));
    nuevo->ant=NULL;
    nuevo->sig=lista.primero;
    nuevo->dato=elemento;

    if(lista.primero==NULL){
        lista.ultimo=nuevo; 
    }else{
        lista.primero->ant=nuevo; 
    }

    lista.primero=nuevo;

    return lista;
}

DList agregar_final(DList lista, int elemento){
    DNodo *nuevo=malloc(sizeof(DNodo));
    nuevo->dato=elemento;
    nuevo->sig=NULL;
    nuevo->ant=lista.ultimo;

    if(lista.primero==NULL){ //esta vacia
        lista.primero=nuevo; 
    }else{
        DNodo *actual=lista.primero;
        while(actual->sig!=NULL){
            actual=actual->sig;
        }
        actual->sig=nuevo; // ya esoy en el ultimo
    }

    /* else{ lista.ultimo->sig=nuevo; }*/

    lista.ultimo=nuevo;

    return lista;
}

void eliminar_inicio(DList *lista){
    if(lista->primero==NULL) return; //nada que eliminar

    DNodo *inicio=lista->primero;
    lista->primero=inicio->sig;  //El nuevo inicio :)

    if(lista->primero==NULL){
        lista->ultimo=NULL;
    }else{
        lista->primero->ant=NULL; //el "viejo" primero
    }

    free(inicio);
}

void eliminar_final(DList *lista){
    if(lista->primero==NULL) return; //nada que eliminar...

    DNodo *final=lista->ultimo;
    lista->ultimo=final->ant;

    if(lista->ultimo==NULL){
        lista->primero=NULL;
    }else{
        lista->ultimo->sig=NULL;
    }

    free(final);
}


void eliminar_en_posicion(DList *lista, int pos){
    if(lista->primero==NULL) return;  //lista vacia...

    if(pos==0){ eliminar_inicio(lista);}
    
    DNodo *inicio=lista->primero;
    int contador=0;

    while(inicio!=NULL && contador<pos){
        inicio=inicio->sig;
        contador++;
    }

    /*for (int contador = 0; contador < pos && actual != NULL; contador++) {
        actual = actual->sig;
    }
    */
    
    if(inicio==NULL) return; //la posicion se excedio....

    // Caso especial: si `pos` apunta al último nodo
    if (inicio == lista->ultimo) {
        eliminar_final(lista);
        return;
    }

    //punteros de los vecinos...
    if (inicio->ant != NULL) {
        inicio->ant->sig = inicio->sig;
    }


    if(inicio->sig!=NULL){
        inicio->sig->ant=inicio->ant;
    }
    
    free(inicio);

}

DNodo* buscar_elemento(DList lista, int elemento){
    if(lista.primero==NULL) return NULL;

    if(lista.primero->dato==elemento) return lista.primero;
    else if(lista.ultimo->dato==elemento) return lista.ultimo;

    DNodo *actual=lista.primero;
    while(actual->sig!=NULL){
        if(actual->dato==elemento){
            return actual;
        }
        actual=actual->sig;
    }

    return NULL; //elemento no encontrado...

}

void eliminar_elemento(DList *lista, int elemento){
    if(buscar_elemento(*lista,elemento)==NULL) return; //el elemento NO existe...

    DNodo *actual=lista->primero;
    while(actual!=NULL){
        if(actual->dato==elemento){
            if(actual->sig!=NULL){
                actual->sig->ant=actual->ant;
            }else{
                lista->ultimo=actual->ant; //ultimo nodo
            }

            if(actual->ant!=NULL){
                actual->ant->sig=actual->sig;
            }else{
                lista->primero=actual->sig; //primer nodo.
            }

            free(actual);
            return;
        }
        actual=actual->sig;
    }

}

void imprimir_lista(DList lista){
    if(lista.primero==NULL){
        printf("Lista vacia\n");
        return;
    }

    DNodo *actual=lista.primero;
    while(actual!=NULL){
        printf("%d<->\t",actual->dato);
        actual=actual->sig;
    }
}

void imprimir_lista_al_reves(DList lista){
    if(lista.primero==NULL){
        printf("Lista vacia\n");
        return;
    }

    DNodo *actual=lista.ultimo;
    while(actual!=NULL){
        printf("%d<->\t",actual->dato);
        actual=actual->ant;
    }
}

int tam_lista(DList lista){
    if(lista.primero==NULL) return 0;
    int contador=0;
    DNodo *actual=lista.primero;
    while(actual!=NULL){
        contador++;
        actual=actual->sig;
    }

    return contador;
}


void  concatenar(DList *l1, DList l2){
    if(l1->primero==NULL){
        l1->primero=l2.primero;
        l1->ultimo=l2.ultimo;
    }

    if(l2.primero==NULL){
        return; //l1 sigue igual...
    }

    l1->ultimo->sig=l2.primero;
    l2.primero->ant=l1->ultimo;

    l1->ultimo=l2.ultimo;


}

DList copiar_lista(DList lista){
    
    DList copy;
    copy.primero=NULL;
    copy.ultimo=NULL;

    if(lista.primero==NULL) return copy;

    DNodo *actual=lista.primero;
    DNodo *antes=NULL;

    while(actual!=NULL){
        DNodo *nuevo=malloc(sizeof(DNodo));
        nuevo->dato=actual->dato;
        nuevo->ant=antes;
        nuevo->sig=NULL;

        if(antes==NULL){
            copy.primero=nuevo;
        }else{
            antes->sig=nuevo;
        }

        antes=nuevo;
        actual=actual->sig;
    }

    copy.ultimo=antes;
    
    return copy;
}

void insertar_en_posicion(DList *lista,int pos,int elemento){
    if(lista->primero==NULL || pos<0) return;

    if(pos==0){*lista=agregar_inicio(*lista,elemento); return;}

    int contador=0;
    DNodo *actual=lista->primero;
    while(actual!=NULL && contador<pos-1){
        contador++;
        actual=actual->sig;
    }

    if(actual==NULL) return; //pos se paso....

    if(actual==lista->ultimo){ *lista=agregar_final(*lista,elemento); return;}


    DNodo *nuevo=malloc(sizeof(DNodo));
    nuevo->dato=elemento;
    nuevo->sig=actual->sig;  //por eso pos-1
    nuevo->ant=actual;

    if(actual->sig!=NULL){
        actual->sig->ant=nuevo;
    }

    actual->sig=nuevo;
}


int main() {
    // Inicializar una lista doblemente enlazada
    DList lista = {NULL, NULL};
    DList otraLista = {NULL, NULL};

    printf("---- Agregar elementos al inicio ----\n");
    lista = agregar_inicio(lista, 10);
    lista = agregar_inicio(lista, 20);
    lista = agregar_inicio(lista, 30);
    imprimir_lista(lista);
    printf("\n");

    printf("---- Agregar elementos al final ----\n");
    lista = agregar_final(lista, 40);
    lista = agregar_final(lista, 50);
    imprimir_lista(lista);
    printf("\n");

    printf("---- Eliminar el primer elemento ----\n");
    eliminar_inicio(&lista);
    imprimir_lista(lista);
    printf("\n");

    printf("---- Eliminar el último elemento ----\n");
    eliminar_final(&lista);
    imprimir_lista(lista);
    printf("\n");

    printf("---- Insertar en posición 2 ----\n");
    insertar_en_posicion(&lista, 2, 25);
    imprimir_lista(lista);
    printf("\n");

    printf("---- Eliminar el elemento 25 ----\n");
    eliminar_elemento(&lista, 25);
    imprimir_lista(lista);
    printf("\n");

    printf("---- Tamaño de la lista ----\n");
    printf("Tamaño de la lista: %d\n", tam_lista(lista));

    printf("---- Crear otra lista ----\n");
    otraLista = agregar_inicio(otraLista, 60);
    otraLista = agregar_inicio(otraLista, 70);
    imprimir_lista(otraLista);
    printf("\n");

    printf("---- Concatenar listas ----\n");
    concatenar(&lista, otraLista);
    imprimir_lista(lista);
    printf("\n");

    printf("---- Copiar lista ----\n");
    DList copia = copiar_lista(lista);
    imprimir_lista(copia);
    printf("\n");

    printf("---- Lista copiada al revés ----\n");
    imprimir_lista_al_reves(copia);
    printf("\n");

    printf("---- Eliminar en posición 3 ----\n");
    eliminar_en_posicion(&lista, 3);
    imprimir_lista(lista);
    printf("\n");

    printf("---- Lista completa ----\n");
    imprimir_lista(lista);
    printf("\n");

    return 0;
}
