// j. 4. ¿Puede fallar la siguiente aserci´on (wr y rd corren en un thread cada uno)? Explique. Si puede
// fallar, arregle el programa.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/select.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h> //POSIX.
#include <assert.h>

volatile int x = 0;
volatile int y = 0; //share var for each thread :)
int turno = 0; // 0: wr, 1: rd

pthread_mutex_t mutex_v = PTHREAD_MUTEX_INITIALIZER;

void *wr(void *arg) {
    pthread_mutex_lock(&mutex_v);
    while (turno != 0) { // Espera activa con exclusión mutua
        pthread_mutex_unlock(&mutex_v);
        pthread_mutex_lock(&mutex_v);
    }

    // Región crítica
    x = 123;
    y = 1;
    turno = 1; // Cambia el turno

    pthread_mutex_unlock(&mutex_v);
    return NULL;
}

void *rd(void *arg) {
    pthread_mutex_lock(&mutex_v);
    while (turno != 1) { // Espera activa con exclusión mutua
        pthread_mutex_unlock(&mutex_v);
        pthread_mutex_lock(&mutex_v);
    }

    // Región crítica
    while (!y);  // Espera que y sea 1
    assert(x == 123); // Verifica la condición
    turno = 0; // Cambia el turno

    pthread_mutex_unlock(&mutex_v);
    return NULL;
}

int main() {
    pthread_t t0, t1;

    pthread_create(&t0, NULL, wr, NULL);
    pthread_create(&t1, NULL, rd, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    pthread_mutex_destroy(&mutex_v);

    assert(x || y);
    return 0;
}

/**
 * Puede fallar ya que puede ocurrir que y==1 pero que aún x no sea 123, al poner volatil ayuda a evitar optimizaciones del compilar pero no garantiza ningún order de ejecución entre hilos
 * Para hacerlo seguro, hab+ia que usar mutexes, barries o memoria at+omica para garantizar el orden de esritura-lectura.
 */


/* con barriers:
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

volatile int x = 0;
volatile int y = 0;
pthread_barrier_t barrier;

void *wr(void *arg) {
    x = 123;
    y = 1;
    pthread_barrier_wait(&barrier); // Asegurar sincronización antes de continuar
    return NULL;
}

void *rd(void *arg) {
    pthread_barrier_wait(&barrier); // Esperar a que `wr` haya terminado
    assert(x == 123);  // Ahora `x` está garantizado antes de esta lectura
    return NULL;
}

int main() {
    pthread_t t0, t1;
    pthread_barrier_init(&barrier, NULL, 2);  // Inicializar barrera para 2 threads

    pthread_create(&t0, NULL, wr, NULL);
    pthread_create(&t1, NULL, rd, NULL);
    
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    
    pthread_barrier_destroy(&barrier);  // Liberar barrera
    return 0;
}*/

/* con mutex_cond:
pthread_mutex_t mutex_v = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_v = PTHREAD_COND_INITIALIZER;

void *wr(void *arg) {
    pthread_mutex_lock(&mutex_v);
    x = 123;
    y = 1;
    pthread_cond_signal(&cond_v); // Señalar que y ha cambiado
    pthread_mutex_unlock(&mutex_v);
    return NULL;
}

void *rd(void *arg) {
    pthread_mutex_lock(&mutex_v);
    while (!y) {  // Esperar hasta que y sea 1
        pthread_cond_wait(&cond_v, &mutex_v);
    }
    assert(x == 123);  // Ahora sí, x debería estar actualizado
    pthread_mutex_unlock(&mutex_v);
    return NULL;
}
*/