// Ej.2(Fil´osofos Comensales, Dijkstra).Cinco fil´osofos se sientan alrededor de una mesa redonda y viven la buena vida alternando entre comer y pensar.Cada fil´osofo tiene su plato de pasta, un tipo particular de fideos que requieren dos tenedores para ser comidos.Entre cada par de fil´osofos consecutivos hay un tenedor, y cada fil´osofo s´olo puede alcanzar los que est´an a su izquierda y derecha.Para comer, los fil´osofos acordaron primero tomar el tenedor a su derecha y luego el de a su izquierda.Si cualquier fil´osofo toma un tenedor y el otro est´a ocupado,
//     se quedar´a esperando, con un tenedor en la mano, hasta que pueda tomar el otro tenedor, para luego empezar a comer.Una vez que un fil´osofo terminar de comer deja los tenedores sobre la mesa y piensa hasta que le vuelve a dar hambre, cuando repite el procedimiento.Una implementaci´on de esta situaci´on con pthreads es como sigue :

// b) Cansados de no comer los fil´osofos deciden pensar una soluci´on a su problema. Uno razona que esto
// no suceder´ıa si alguno de ellos fuese zurdo y tome primero el tenedor de su izquierda. Implemente
// esta soluci´on y explique por qu´e funciona


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define N_FILOSOFOS 5
#define ESPERA 5000000
pthread_mutex_t tenedor[N_FILOSOFOS];
pthread_mutex_t *izq(int i) { return &tenedor[i]; }
pthread_mutex_t *der(int i) { return &tenedor[(i + 1) % N_FILOSOFOS]; }
void pensar(int i)
{
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
    if(i%2==0){ //diestro
        pthread_mutex_lock(der(i));
        pthread_mutex_lock(izq(i));
    } else{
        pthread_mutex_lock(izq(i));
        pthread_mutex_lock(der(i));
    }
}
void dejar_tenedores(int i)
{   if(i%2==0){ //diestro
        pthread_mutex_unlock(der(i));
        pthread_mutex_unlock(izq(i));
    }else{
        pthread_mutex_unlock(izq(i));
        pthread_mutex_unlock(der(i));
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



/* Funciona porque, siempre se va alternando entre diestro - zurdo.
Es decir, ROMPEMOS el circular wait. */