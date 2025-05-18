// Ej.6(Problema de los Fumadores, Patil).Tres procesos tratan de fumar cada vez que pueden.Para hacerlo necesitan tres ingredientes : tabaco, papel y f´osforos.Cada uno tiene una cantidad ilimitada de uno de estos ingredientes.Esto es, un fumador tiene tabaco, otro tiene papel y el ´ultimo tiene f´osforos.Los fumadores no se prestan los ingredientes entre ellos, pero hay un cuarto proceso, el agente, con cantidad ilimitada de todos los ingredientes, que repetidamente pone a disposici´on de los fumadores dos de los tres ingredientes, eligi´endolos al azar.Cada vez que esto pasa, el fumador que tiene el ingrediente restante deber´ıa proceder a hacerse un cigarrillo y fumar.Al terminar de fumar(y no antes) el fumador avisa al agente que termin´o, para que el mismo pueda seguir atendiendo.A continuaci´on se puede ver una implementaci´on ingenua con pthreads :

//!3 procesos quieren fumar, necesitan tabaco papel y fosforos. no se prestan. el agente si 2/3 ingred. reparte

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t tabaco, papel, fosforos, otra_vez;

void agente()
{
    while (1)
    {
        sem_wait(&otra_vez);
        int caso = random() % 3;  //reparte aleatoriamente un ingrediente.
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
    {
        sem_wait(&tabaco);
        sem_wait(&papel);
        fumar(1);
        sem_post(&otra_vez);
    }
}
void *fumador2(void *arg)  //tiene papel - espera fosforos y tabaco
{
    while (1)
    {
        sem_wait(&fosforos);
        sem_wait(&tabaco);
        fumar(2);
        sem_post(&otra_vez);
    }
}
void *fumador3(void *arg)  //tiene tabaco - espera papel y fosforos
{
    while (1)
    {
        sem_wait(&papel);
        sem_wait(&fosforos);
        fumar(3);
        sem_post(&otra_vez);
    }
}
int main()
{
    pthread_t s1, s2, s3;
    sem_init(&tabaco, 0, 0);
    sem_init(&papel, 0, 0);
    sem_init(&fosforos, 0, 0);
    sem_init(&otra_vez, 0, 1);
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

//* a) ¿C´omo puede ocurrir un deadlock en esta implementaci´on ingenua?
// Puede ocurrir que un fumador fume pero no avise al agente, entonces se queda sin recursos para fumar y, el agente no es notificado que reparta al azar. Es decir, los 3 fumadores esperan los ingredientes antes de que el agente es avisado de que un fumador ha terminado para poder reponer. Los 3 se bloquean esperando ingredientes,que fueron consumidos por otros -- que a su vez, esperan ingredientes.

//* b) ¿Pueden ordenarse los recursos para evitar el problema?
//No, el orden no importaria. Lo que sucede es mala sincronización de semáforos.


//* d) Piense soluciones alternativas si fuera aceptable modificar al agente.
Una posible alternativa sería de usar variables de condición, para asegurar que el agente solamente notifique al fumador que le falta el recurso que éste provee.

//* e) Extra: ¿c´omo se relaciona este ejercicio al servidor de turnos de la pr´actica anterior?
//Se relaciona con que, los fumadores deben respetar "cierto turno" ya que NO pueden fumar al mismo tiempo (ninguno posee los 3 ingredientes al mismo tiempo, solo 1 de ellos) y el agente es el encargado de dar los tickets de turnos a ellos.


