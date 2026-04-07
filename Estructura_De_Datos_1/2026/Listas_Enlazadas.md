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

typedef struct _SList {
    SNodo *primero; 
    SNodo *ultimo;
} SList;

