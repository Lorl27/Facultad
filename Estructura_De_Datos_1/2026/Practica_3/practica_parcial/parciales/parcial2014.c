//1)  Una pila, formada de 2 colas.

/*
Queremos que q1 sea siempre nuestra estructura principal y que el elemento más nuevo esté siempre al frente 
(listo para salir con un simple Dequeue). 
q2 siempre estará vacía esperando para ayudar.

Imagina que apilamos el número 1, y luego el número 2:

Llega el 2: Lo encolamos en la cola vacía q2. (Estado: q1 = [1], q2 = [2]).

El Trasvase: Desencolamos todo lo que haya en q1 y lo encolamos detrás del 2 en q2. (Estado: q1 = [], q2 = [2, 1]).

El Intercambio: Cambiamos las etiquetas (punteros). Lo que era q2 ahora se llama q1, y viceversa. 
(Estado: q1 = [2, 1], q2 = []).

¡Magia! El 2 quedó al frente de q1. Cuando hagamos Pop, simplemente desencolamos de q1 y saldrá el 2.

*/
#include <stdio.h>
#include <stdlib.h>


typedef XQueue;

typedef struct XStack
{
    XQueue * q1;
    XQueue * q2;    
}*XStack;


// 1. Crear la pila instanciando sus dos colas internas
XStack xstack_create() {
    XStack stack = malloc(sizeof(XStack));
    stack->q1 = xqueue_create();
    stack->q2 = xqueue_create();
    return stack;
}

// 2. ¿Está vacía? 
// Como q1 es la principal, si q1 está vacía, toda la pila lo está.
int xstack_is_empty(XStack stack) {
    return xqueue_is_empty(stack->q1);
}

// 3. Push (El trabajo pesado de reordenamiento)
void xstack_push(XStack stack, void *dato) {
    // Paso 1: El nuevo elemento entra a la sala de espera (q2)
    xqueue_enqueue(stack->q2, dato);

    // Paso 2: Mudamos todo lo viejo detrás del nuevo
    while (!xqueue_is_empty(stack->q1)) {
        void *viejo = xqueue_top(stack->q1);
        xqueue_dequeue(stack->q1);
        xqueue_enqueue(stack->q2, viejo);
    }

    // Paso 3: Swapeamos los punteros para que q1 vuelva a ser la cola oficial
    XQueue *temp = stack->q1;
    stack->q1 = stack->q2;
    stack->q2 = temp;
}

// 4. Pop (Trabajo ligero gracias al Push)
void* xstack_pop(XStack stack) {
    if (xstack_is_empty(stack)) return NULL;
    
    // Como en el push ya pusimos el último elemento al frente, 
    // hacer Pop es tan simple como desencolar la principal.
    return xqueue_dequeue(stack->q1);
}