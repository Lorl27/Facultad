# Lista Enlazada:
Estructura dinàmica formada por nodos, conectados a travès de un puntero.
En estos nodos, se almacena la informaciòn de los elementos de la lista.

**Nodo de una lista:**
- Informaciòn
- Puntero al sig. elemento.


```c
typedef struct _SNodo {
    int dato;
    struct _SNodo *siguiente;
} SNodo;
```

**Uso**
```c 
SNodo * nuevoNodo=malloc(sizeof(SNodo));
```

**Construcciòn de la lista**
1- Crear un nuevo nodo inicial y hacer que su siguiente apunte al anterior 
    La desventaja de esto es que se cambia el inicio.

    
```c 
    
    SNodo * nuevoInicial = malloc(sizeof(SNodo));
    nuevoInicial->dato=5; nuevoInicial->sig=NULL;

    SNodo * nodoInicial = malloc(sizeof(SNodo));
    nodoInicial->dato=7;
    nodoInicial->sig=nuevoInicial;

```
    

2- Ir guardando en 'siguiente' del ùltimo nodo, la direcciòn del sig. nodo.
    Para averiguar cuàl es el ùltimo nodo, hay que ir al nodo / siguiente=NULL
    Es decir:
```c 
        SNodo * nuevoNodo=malloc(sizeof(SNodo));
        nuevoNodo->dato=5;nuevoNodo->sig=NULL;

        if(inicio==NULL) inicio=nuevoNodo;
        else{
            SNodo * temp=inicio;
            for( ; temp->sig!=NULL; temp=temp->sig){
                ;
            }

            //llegamos al ultimo
            temp->sig=nuevoNodo;
        }
        return inicio;
```
# Prototipo de funciòn:
1-
```c
    SNodo * funcion(SNodo* lista, int dato);

        SNodo * agregar_al_inicio(SNodo* lista, int dato){
            SNodo * nuevoNodo=malloc(sizeof(SNodo));
            nuevoNodo->dato=dato; nuevoNodo->sig=lista;
            return nuevoNodo;
        }
    
    int main(){
        SNodo * lista=NULL;
        lista=agregar_al_inicio(lista,9);
    }


```
2- 
```c
    void funcion(SNodo** lista, int dato);

        void agregar_al_inicio(SNodo** lista, int dato){
            SNodo * nuevoNodo=malloc(sizeof(SNodo));
            nuevoNodo->dato=dato; nuevoNodo->sig= *lista;
            * lista = nuevoNodo;
        }

        int main(){
        SNodo * lista=NULL;
        lista=agregar_al_inicio(&lista,9);
    }

```

# Funcion recursiva
```c
SNodo * agregar_final(SNodo * lista, int dato){
    if(lista==NULL){
        SNodo* nuevoNodo=malloc(sizeof(SNodo));
        nuevoNodo->dato=dato; nuevoNodo->sig=NULL;
        return nuevoNodo;
    }else{
        lista->sig=agregar_final(lista->sig,dato);
        return lista;
    }
}
```

# SLIST

```c
typedef SNodo *SList;
```

```c
typedef struct _SListEsctructura {
    SNodo *primero; 
    SNodo *ultimo;
} SListEsctructura;

typedef SListEsctructura * SList;
```

# DNodo y DList:

```c
typedef struct _DNodo{
    struct _DNodo * sig;
    int dato;
    struct _DNodo *ant;
} DNodo;
```


```c
typedef struct _DListEstructura{
    DNodo *primero; 
    DNodo *ultimo;
} DListEstructura;

typedef DListEstructura * DList;
```
# Listas circulares:
**SIMPLE** El siguiente del último elemento de la lista apunta al primero 

-Cada nodo tiene un puntero al siguiente.

-El último nodo apunta nuevamente al primero.

-Esto permite recorrer la lista indefinidamente en un ciclo.(NO existe NULL - hay que usar DO WHILE)

### Lista Circular Simple
(lista → 4 → 7 → 3 → 6 ↘)
         ↖──────


```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    return nuevo;
}

int main() {
    // Crear nodos
    Nodo* n1 = crearNodo(4);
    Nodo* n2 = crearNodo(7);
    Nodo* n3 = crearNodo(3);
    Nodo* n4 = crearNodo(6);

    // Enlazar
    n1->siguiente = n2;
    n2->siguiente = n3;
    n3->siguiente = n4;
    n4->siguiente = n1; // último apunta al primero

    // Recorrer 8 pasos para mostrar el ciclo
    Nodo* actual = n1;
    for (int i = 0; i < 8; i++) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("...\n");

    return 0;
}
```




**DOBLE** El anterior del primero es el último de la lista

-Cada nodo tiene dos punteros: uno al siguiente y otro al anterior.

-El último nodo apunta al primero como "siguiente".

-El primero apunta al último como "anterior".

-Se puede recorrer en ambas direcciones sin fin. (NO EXISTE NULL !). Es necesario hacer un 
```c
DNodo * tmp = lista->primero;
do {tmp=tmp->sig;} while (tmp!=lista->primero);
```


### Lista Circular Doble
(lista ⇄ 8 ⇄ 4 ⇄ 3 ⇄)
        ↖───────────↙


```c
        #include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

int main() {
    // Crear nodos
    Nodo* n1 = crearNodo(8);
    Nodo* n2 = crearNodo(4);
    Nodo* n3 = crearNodo(3);

    // Enlazar doblemente
    n1->siguiente = n2;
    n2->siguiente = n3;
    n3->siguiente = n1; // último apunta al primero

    n1->anterior = n3;  // primero apunta al último
    n2->anterior = n1;
    n3->anterior = n2;

    // Recorrer hacia adelante
    Nodo* actual = n1;
    for (int i = 0; i < 6; i++) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("...\n");

    // Recorrer hacia atrás
    actual = n1;
    for (int i = 0; i < 6; i++) {
        printf("%d <- ", actual->dato);
        actual = actual->anterior;
    }
    printf("...\n");

    return 0;
}
```


# LISTAS SIMPLEMENTE ENLAZADAS GENERALES:
- Se usan datos genericos de tipo void * y, se delega el trabajo a funciones auxiliares.
- AL insertar datos, se precisa copia fìsica.


```c
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}


GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  if (newNode == NULL) return NULL; 
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}


```