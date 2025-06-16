// Este problema proviene del libro *Operating Systems* de William Stallings [11], pero él lo atribuye a John Trono de St. Michael’s College en Vermont.

// Santa Claus duerme en su tienda en el Polo Norte y solo puede ser despertado por:
// 1. Que los nueve renos hayan regresado de sus vacaciones en el Pacífico Sur.
// 2. Que algunos elfos tengan dificultades para fabricar juguetes; sin embargo, para que Santa pueda descansar, los elfos solo pueden despertarlo cuando tres de ellos tienen problemas. 

// Cuando tres elfos están teniendo sus problemas resueltos, cualquier otro elfo que quiera visitar a Santa debe esperar a que esos elfos regresen. Si Santa se despierta y encuentra tres elfos esperando en la puerta de su tienda, junto con el último reno que regresa de los trópicos, Santa decide que los elfos pueden esperar hasta después de Navidad, ya que es más importante preparar su trineo. (Se supone que los renos no quieren salir de los trópicos y, por lo tanto, permanecen allí hasta el último momento posible). El último reno en llegar debe ir a buscar a Santa, mientras que los otros esperan en una cabaña de calentamiento antes de ser enganchados al trineo.

// ### Especificaciones adicionales:
// - Después de que llega el noveno reno, Santa debe invocar `prepareSleigh`, y luego los nueve renos deben invocar `getHitched`.
// - Después de que llega el tercer elfo, Santa debe invocar `helpElves`. Al mismo tiempo, los tres elfos deben invocar `getHelp`.
// - Los tres elfos deben invocar `getHelp` antes de que puedan entrar otros elfos (incrementar el contador de elfos).

// Santa debe ejecutar este proceso en un bucle para poder ayudar a varios grupos de elfos. Se asume que hay exactamente 9 renos, pero puede haber cualquier número de elfos.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define RENOS 9
#define MAX_ELFOS 15

sem_t sem_santa;          // Santa espera acá
sem_t sem_renos;          // Para que los renos esperen a ser enganchados
sem_t sem_ayuda_elfos;    // Para que los elfos esperen a ser ayudados
pthread_mutex_t mutex;
pthread_mutex_t mutex_elfos; // limita el acceso de los elfos a grupos de 3

int contador_renos = 0;
int contador_elfos = 0;

void prepararCarro() { printf("Santa prepara el trineo!\n"); }
void ObtenerAyuda(int id) { printf("Santa ayuda al elfo %d\n", id); }
void engancharReno(int id) { printf("Reno %d enganchado.\n", id); }

void* santa(void* arg) {
    while (1) {
        sem_wait(&sem_santa); // espera ser despertado

        pthread_mutex_lock(&mutex);
        if (contador_renos == RENOS) {
            prepararCarro();
            for (int i = 0; i < RENOS; i++) {
                sem_post(&sem_renos); // deja enganchar a los renos
            }
            contador_renos = 0;
        } else if (contador_elfos == 3) {
            for (int i = 0; i < 3; i++) {
                sem_post(&sem_ayuda_elfos); // permite que los 3 elfos reciban ayuda
            }
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* reno(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    contador_renos++;
    if (contador_renos == RENOS) {
        sem_post(&sem_santa); // el último reno despierta a Santa
    }
    pthread_mutex_unlock(&mutex);

    sem_wait(&sem_renos); // espera ser enganchado
    engancharReno(id);
    return NULL;
}

void* elfo(void* arg) {
    int id = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&mutex_elfos);

        pthread_mutex_lock(&mutex);
        contador_elfos++;
        if (contador_elfos == 3) {
            sem_post(&sem_santa); // el tercer elfo despierta a Santa
        }
        pthread_mutex_unlock(&mutex);

        sem_wait(&sem_ayuda_elfos); // espera que Santa lo ayude
        ObtenerAyuda(id);

        pthread_mutex_lock(&mutex);
        contador_elfos--;
        if (contador_elfos == 0) {
            pthread_mutex_unlock(&mutex_elfos); // permite que entren otros 3
        }
        pthread_mutex_unlock(&mutex);
        sleep(1); // simula tiempo entre problemas
    }
}


int main() {
    pthread_t santa_tid, renos_tid[RENOS], elfos_tid[MAX_ELFOS];
    int id[RENOS > MAX_ELFOS ? RENOS : MAX_ELFOS];

    sem_init(&sem_santa, 0, 0);
    sem_init(&sem_renos, 0, 0);
    sem_init(&sem_ayuda_elfos, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex_elfos, NULL);

    pthread_create(&santa_tid, NULL, santa, NULL);

    for (int i = 0; i < RENOS; i++) {
        id[i] = i + 1;
        pthread_create(&renos_tid[i], NULL, reno, &id[i]);
    }

    for (int i = 0; i < MAX_ELFOS; i++) {
        id[i] = i + 1;
        pthread_create(&elfos_tid[i], NULL, elfo, &id[i]);
    }

    pthread_join(santa_tid, NULL);
    return 0;
}
