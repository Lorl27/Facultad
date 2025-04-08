/* PROBLEMA DEL JARDIN ORNAMENTAL
*
* Tenemos un bonito jardín que está abierto al publico que debe pagar una entrada para disfrutar de él.
* La entrada es controlada por dos hilos, los gerentes del jardin desean que en cada momento puedan saber cuantas personas hay dentro
* Queremos hacer una sencilla simulacion de su funcionamiento
*   Cada hilo sera manejado por un procespo separado en el programa
*   Los procesos de los hilos se ejecutaran concurrentemente
*   Usamos una variable global para controlar el numero actual de vistiantes
*   Simulamos que entran 20 por cada hilo y mostramos el resultado
*/

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

#define N 2  // nros procesos

volatile int turno;
volatile int interesados[N];

void* entrar_region(void* arg){
    int proceso=(int)arg;
    printf("[%d] quiere ir al jardin \n",proceso);
    
    interesados[proceso]=1;  //existe alguien q quiere ir
    printf("[%d] entro al jardin \n",proceso);
    return NULL;
}

void* salir_region(void* arg){
    int proceso=(int)arg;
    interesados[proceso] = 0;
    printf("[%d] salio del jardin \n",proceso);
    return NULL;

}

int main(){
    pthread_t hilo1;
    pthread_t hilo2;

    printf("El jardin ornamental abrio \n");

    pthread_create(&hilo1,NULL,entrar_region,(void *)0);
    pthread_create(&hilo2,NULL,entrar_region,(void*)1);

    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);

    printf("Ahora, se van todos.\n");

    pthread_create(&hilo1, NULL, salir_region, (void*)0);
    pthread_create(&hilo2, NULL, salir_region, (void*)1);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    return 0;

}