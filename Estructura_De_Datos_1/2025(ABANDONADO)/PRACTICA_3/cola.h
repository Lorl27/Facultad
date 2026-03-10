#ifndef __COLA_H__
#define __COLA_H__

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

typedef struct _Cola{
    GList primero;  //son punteros
    GList ultimo;
} Cola;

typedef void (*FuncionDestructoraCola)(void *dato);
typedef void *(*FuncionCopiaCola)(void *dato);

// Crea una cola vacía
Cola *cola_crear();

// Encola un dato
void cola_encolar(Cola *cola, void *dato, FuncionCopiaCola copiar);

// Devuelve el dato al frente (sin desencolar)
void *cola_inicio(Cola *cola);

// Desencola y destruye el dato
void cola_desencolar(Cola *cola, FuncionDestructoraCola destruir);

// Libera toda la cola
void cola_destruir(Cola *cola, FuncionDestructoraCola destruir);

// Devuelve 1 si está vacía, 0 si no
int cola_empty(Cola *cola);

void cola_imprimir(Cola *cola, void (*mostrar)(void *));


#endif /* __COLA_H__ */