// Ej.7(Cola Lock - Free, Lamport).El siguiente fragmento implementa una cola concurrente entre dos procesos.La variable s mantiene la cantidad de elementos escritos y r los le´ıdos.El valor K est´a para que estas variables no crezcan demasiado(s y r siempre est´an entre 0 y K - 1).

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define B 2
#define K (2 * B)

volatile int cant_elementos_escritos=0,cant_elementos_leidos=0, buf[B];  

static inline int diff() {
    return (K + cant_elementos_escritos - cant_elementos_leidos) % K;
}


void *prod(void *_arg)
{
    int cur = 0;
    while (1)
    {
        while (diff() == B) {;}  //buffer lleno

        buf[cant_elementos_escritos % B] = cur++;  //escribo en buffer
        cant_elementos_escritos = (cant_elementos_escritos + 1) % K;  //escribo
    }
}
void *cons(void *_arg)
{
    int cur;
    while (1)
    {
        while (diff() == 0){;}  //buffer vacio

        cur = buf[cant_elementos_leidos % B]; //leo desde buffer
        cant_elementos_leidos = (cant_elementos_leidos + 1) % K;
        printf("Lei %d\n", cur);
    }
}

int main() {
    pthread_t h_prod, h_cons;

    // Crear hilos productor y consumidor
    pthread_create(&h_prod, NULL, prod, NULL);
    pthread_create(&h_cons, NULL, cons, NULL);

    // Esperar (nunca terminan en este caso)
    pthread_join(h_prod, NULL);
    pthread_join(h_cons, NULL);

    return 0;
}

//* Explique por qu´e funciona sin usar mutexes ni ninguna primitiva de sincronizaci´on. ¿Puede generalizar a
//* n procesos?

//Funciona porque cada uno accede a solo una variable y el buffer se usa de diferente forma para c/u/
//r y s se actulizan SOLAMENTE por 1 produto y 1 consumidor, resp. por lo que no hay RACE CONDITION
// Se evita que accedan al mismo tiempo al buffer, ya que si esta vacio, se espera. si esta lleno, espera.  -->DIFF ES BUSY WAIT!

//Se podría pero deberias agregar mutex o semaforos