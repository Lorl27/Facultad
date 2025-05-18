// Ej.6(Problema de los Fumadores, Patil).Tres procesos tratan de fumar cada vez que pueden.Para hacerlo necesitan tres ingredientes : tabaco, papel y f´osforos.Cada uno tiene una cantidad ilimitada de uno de estos ingredientes.Esto es, un fumador tiene tabaco, otro tiene papel y el ´ultimo tiene f´osforos.Los fumadores no se prestan los ingredientes entre ellos, pero hay un cuarto proceso, el agente, con cantidad ilimitada de todos los ingredientes, que repetidamente pone a disposici´on de los fumadores dos de los tres ingredientes, eligi´endolos al azar.Cada vez que esto pasa, el fumador que tiene el ingrediente restante deber´ıa proceder a hacerse un cigarrillo y fumar.Al terminar de fumar(y no antes) el fumador avisa al agente que termin´o, para que el mismo pueda seguir atendiendo.A continuaci´on se puede ver una implementaci´on ingenua con pthreads :

//!3 procesos quieren fumar, necesitan tabaco papel y fosforos. no se prestan. el agente si 2/3 ingred. reparte

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t tabaco, papel, fosforos, otra_vez;

sem_t mutex;

void agente()
{
    while (1)
    {
        sem_wait(&otra_vez);
        int caso = random() % 3;  //reparte aleatoriamente 2 ingredientes.
        if (caso != 0)
            sem_post(&fosforos);
        if (caso != 1)
            sem_post(&papel);
        if (caso != 2)
            sem_post(&tabaco);
    }
}
void fumar(int fumador)
{
    printf("Fumador %d: Puf! Puf! Puf!\n", fumador);
    sleep(1);
}
void *fumador1(void *arg)  //tiene fosforos- espera tabacos y papel
{
    while (1)
    {   sem_wait(&mutex);

        if(sem_trywait(&tabaco)<0){  //si no hay tabaco, sale
            sem_post(&mutex); continue;
        }

        if(sem_trywait(&papel)<0){  //Si no hay papel, sale Y devuelve el tabaco que tomo.
            sem_post(&tabaco);
            sem_post(&mutex);continue;
        }

        fumar(1);
        sem_post(&otra_vez);
        sem_post(&mutex);
    }
}
void *fumador2(void *arg)  //tiene papel - espera fosforos y tabaco
{
    while (1)
    {   sem_wait(&mutex);
        if(sem_trywait(&fosforos)<0){
            sem_post(&mutex);continue;
        }
        if(sem_trywait(&tabaco)<0){
            sem_post(&fosforos);
            sem_post(&mutex);continue;
        }
        fumar(2);
        sem_post(&otra_vez);
        sem_post(&mutex);
    }
}
void *fumador3(void *arg)  //tiene tabaco - espera papel y fosforos
{
    while (1)
    {   sem_wait(&mutex);
        if(sem_trywait(&papel)<0){
            sem_post(&mutex);continue;
        }
        if(sem_trywait(&fosforos)<0){
            sem_post(&papel);
            sem_post(&mutex);continue;
        }
        fumar(3);
        sem_post(&otra_vez);
        sem_post(&mutex);
    }
}
int main()
{
    pthread_t s1, s2, s3;
    sem_init(&tabaco, 0, 0);
    sem_init(&papel, 0, 0);
    sem_init(&fosforos, 0, 0);
    sem_init(&otra_vez, 0, 1);
    sem_init(&mutex, 0, 1);

    pthread_create(&s1, NULL, fumador1, NULL);
    pthread_create(&s2, NULL, fumador2, NULL);
    pthread_create(&s3, NULL, fumador3, NULL);
    agente();
    return 0;
}

//? El problema consiste en garantizar que el sistema progresa normalmente, es decir que los fumadores toman
//? los ingredientes cuando les corresponde, fuman, y luego notifican al agente que se puede continuar. Los
//? fumadores deben sincronizar entre ellos; no debe modificarse al agente en lo m´as min´ımo. S´ı pueden
//? crearse nuevos sem´aforos, mutexes, y threads.



// c) Implemente una soluci´on (recuerde: sin modificar al agente) y expl´ıquela.
