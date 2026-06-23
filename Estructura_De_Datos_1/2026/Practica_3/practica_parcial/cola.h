#ifndef __COLA_H__
#define __COLA_H__

typedef struct _SNodo
{
    void * dato;
    struct _SNodo * sig;
} SNodo;

typedef struct _Cola {
    SNodo *inicio; // Por aquí salen (dequeue)
    SNodo *fin;    // Por aquí entran (enqueue)
} *Cola;

typedef void * (*FuncionCopia)(void * dato);
typedef void (*FuncionDestructora)(void * dato);
typedef void (*FuncionVisitante)(void * dato);


/*
* Crea la Cola
*/
Cola Cola_crear();

/*
Inserta el elemento al final de la Cola, utilizando la funcion copia pasada por paràmetro
*/
Cola  Encolar(Cola cola, void * elemento, FuncionCopia copy);

/*
Devuelve 1 si la Cola pasada esta vacia y, 0 en caso contrario
*/
int isEmpty(Cola cola);

/*
Elimina el elemento al inicio de la Cola, utilizando la funcion destroy pasada por paràmetro
*/
Cola  Desencolar(Cola cola, FuncionDestructora destroy);

/* 
Destruye toda la COla
*/
Cola cola_destruir(Cola cola, FuncionDestructora destroy);

/*
Recorre la cola usando la funcion pasada por parametro
*/
void cola_recorrer(Cola cola, FuncionVisitante fun);

// Devuelve el primer elemento de la COla
void * Tope(Cola cola);
#endif