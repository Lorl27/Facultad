#ifndef __PILA_H__
#define __PILA_H__

typedef struct _SNodo
{
    void * dato;
    struct _SNodo * sig;
} SNodo;


typedef struct _Pila {
    SNodo * inicio; //El tope
}  * Pila ;


typedef void * (*FuncionCopia)(void * dato);
typedef void (*FuncionDestructora)(void * dato);
typedef void (*FuncionVisitante)(void * dato);


/*
* Crea la pila
*/
Pila pila_crear();

/*
Inserta el elemento al inicio de la Pila, utilizando la funcion copia pasada por paràmetro
*/
Pila  Push(Pila  pila, void * elemento, FuncionCopia copy);

/*
Devuelve 1 si la Pila pasada esta vacia y, 0 en caso contrario
*/
int isEmpty(Pila  pila);

/*
Elimina el elemento al inicio de la Pila, utilizando la funcion destroy pasada por paràmetro
*/
Pila  Pop(Pila  pila, FuncionDestructora destroy);

/* 
Retorna el elemento en el tope de la Pila.
Si la Pila esta vacia, retorna NULL
*/
void * Top(Pila  pila);

/* 
Destruye toda la Pila
*/
Pila pila_destruir(Pila  pila, FuncionDestructora destroy);


/*
Recorre la pila usando la funcion pasada por parametro
*/
void pila_recorrer(Pila pila, FuncionVisitante fun);

#endif