// Ej. 2 (Fil´osofos Comensales, Dijkstra). Cinco fil´osofos se sientan alrededor
// de una mesa redonda y viven la buena vida alternando entre comer y pensar.
// Cada fil´osofo tiene su plato de pasta, un tipo particular de fideos que requieren
// dos tenedores para ser comidos. Entre cada par de fil´osofos consecutivos hay un
// tenedor, y cada fil´osofo s´olo puede alcanzar los que est´an a su izquierda y derecha.
// Para comer, los fil´osofos acordaron primero tomar el tenedor a su derecha y luego
// el de a su izquierda. Si cualquier fil´osofo toma un tenedor y el otro est´a ocupado,
// se quedar´a esperando, con un tenedor en la mano, hasta que pueda tomar el otro
// tenedor, para luego empezar a comer. Una vez que un fil´osofo terminar de comer
// deja los tenedores sobre la mesa y piensa hasta que le vuelve a dar hambre, cuando
// repite el procedimiento.
// Una implementaci´on de esta situaci´on con pthreads es como sigue:
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define N_FILOSOFOS 5
#define ESPERA 5000000 //microsegundo  :)

pthread_mutex_t tenedor[N_FILOSOFOS];
pthread_mutex_t *izq(int i){
    return &tenedor[i];
}
pthread_mutex_t *der(int i) {
    return &tenedor[(i + 1) % N_FILOSOFOS];
}

void pensar(int i){
    printf("Filosofo %d pensando...\n", i);
    usleep(random() % ESPERA);
}

void comer(int i)
{
    printf("Filosofo %d comiendo...\n", i);
    usleep(random() % ESPERA);
}

void tomar_tenedores(int i)
{   
    
    if(N_FILOSOFOS%2!=0){
        pthread_mutex_lock(izq(i));
        pthread_mutex_lock(der(i));
    }else{
        pthread_mutex_lock(der(i));
        pthread_mutex_lock(izq(i));
    }
}

void dejar_tenedores(int i)
{
    if(N_FILOSOFOS%2!=0){
        pthread_mutex_unlock(izq(i));
        pthread_mutex_unlock(der(i));
    }else{
        pthread_mutex_unlock(der(i));
        pthread_mutex_unlock(izq(i));
    }
    
}
void *filosofo(void *arg)
{
    int i = arg - (void *)0;
    while (1)
    {
        tomar_tenedores(i);
        comer(i);
        dejar_tenedores(i);
        pensar(i);
    }
}
int main()
{
    pthread_t filo[N_FILOSOFOS];
    int i;
    for (i = 0; i < N_FILOSOFOS; i++)
        pthread_mutex_init(&tenedor[i], NULL);
    for (i = 0; i < N_FILOSOFOS; i++)
        pthread_create(&filo[i], NULL, filosofo, i + (void *)0);
    pthread_join(filo[0], NULL);
    return 0;
}

// a) Este programa puede terminar en deadlock. Explique c´omo.
/* ERA OBVIO. 
Si cualquier fil´osofo toma un tenedor y el otro est´a ocupado,
// se quedar´a esperando, DEADLOCK! se puede quedar esperando indefinidamente. */

// b) Cansados de no comer los fil´osofos deciden pensar una soluci´on a su problema. Uno razona que esto no suceder´ıa si alguno de ellos fuese zurdo y tome primero el tenedor de su izquierda. Implemente esta soluci´on y explique por qu´e funciona.



// c) Otro fil´osofo piensa que tampoco tendr´ıan el problema si todos fuesen diestros pero s´olo intentasen
// comer a lo sumo N − 1 de ellos a la vez.
// Implemente esta soluci´on y explique por qu´e funciona. Para ello va a necesitar un sem´aforo de
// Dijkstra. Puede utilizar los POSIX Semaphores. En la cabecera semaphore.h puede encontrar los
// prototipos de las funciones necesarias:
// int sem_init(sem_t *sem, int pshared, unsigned int value);
// int sem_destroy(sem_t *sem);
// int sem_wait(sem_t *sem);
// int sem_post(sem_t *sem);
// d) Un fil´osofo, ya sufriendo secuelas del hambre, sugiere que los comensales suelten su tenedor derecho
// si encuentran que el izquierdo ya est´a tomado, posiblemente esperando un tiempo antes de reintentar
// tomarlo. Implemente esta variante e invest´ıguela. ¿Funciona? ¿Es eficiente? Cuantifique su respuesta.
