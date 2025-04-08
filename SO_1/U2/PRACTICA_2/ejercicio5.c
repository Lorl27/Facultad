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

/**
 *  *ALGORITMO DE PETERSON:
 * Se usan 2 variables compartidas: int interesed[2] , que  señala si el proceso quiere entrar 
 * int turn -> de quien es el turno de entrar.abort
 * 
 * sup E proceso 0 y 1 , el proceso que quiere entrar hace esto:
 *  interested[yo] = 1;      // Me interesa entrar
 *  turn = elOtro;           // Le doy el turno al otro
 *  while (interested[elOtro] && turn == elOtro); // Espero si él quiere y es su turno
 *    === Región crítica ===
 * 
 * Y cuando termina,
 * interested[yo] = 0; // Ya no me interesa


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
volatile int interesados[N]={0}; //Ninguno quiere entrar al inicio.

void* entrar_region(void* arg){
    int proceso=(int)arg;
    int otro_Proceso=1-proceso; //si soy 1, será 0. 

    printf("[%d] quiere ir al jardin \n",proceso); //p0 quiere entrar
    
    interesados[proceso]=1;  //existe alguien q quiere ir - le doy el turno a p1
    turno=otro_Proceso;

    while(interesados[otro_Proceso]&& turno==otro_Proceso){ //? "Si P1 también quiere entrar y le di el turno a él, espero..."
        //espera activa.
    }

    //REGIÓN CRÍTICA:
    printf("[%d] entro al jardin \n",proceso);
    sleep(2);
    printf("[%d] salió del jardín\n", proceso);

    //SALIR REGION CRÍTICA:
    interesados[proceso]=0; //p0 sale y como p1 estaba en espera cuando le dio el turno a él - ahora si pued eentrar.
    return NULL;
}

void* salir_region(void* arg){
    int proceso=(int)arg;
    interesados[proceso] = 0;
    printf("[%d] salio del jardin \n",proceso);
    return NULL;

}

int main(){
    pthread_t hilos[N];

    printf("El jardin ornamental abrio \n");

    pthread_create(&hilos[0],NULL,entrar_region,(void *)0);
    pthread_create(&hilos[1],NULL,entrar_region,(void*)1);

    pthread_join(hilos[0],NULL);
    pthread_join(hilos[1],NULL);

    printf("Ahora, se fueron todos.\n");


    return 0;

}


/** 🧍 Paso 1: P0 quiere entrar
            interested[0] = 1;  // "Quiero entrar"
            turn = 1;           // "Le doy el turno al otro (P1)"
P0 ahora espera si:
    while (interested[1] && turn == 1)
➡️ Traducción: "Si P1 también quiere entrar y le di el turno a él, espero..."

Pero P1 aún no quiere entrar, así que:
    interested[1] = 0
Entonces P0 entra al jardín 🏞️

🏃‍♀️ Paso 2: P1 también quiere entrar (mientras P0 ya está adentro)
        interested[1] = 1;  // "Yo también quiero"
        turn = 0;           // "Le doy el turno a P0"
Ahora P1 evalúa:
    wh ile (interested[0] && turn == 0)
➡️ Traducción: "¿P0 quiere entrar y le di el turno a él? Entonces espero..."
✅ Sí, porque P0 sigue adentro y turn == 0.
Entonces P1 espera afuera 🚫

🚪 Paso 3: P0 termina y sale
     interested[0] = 0;  // "Ya no me interesa el jardín"
Ahora, P1 reevalúa:
    while (interested[0] && turn == 0) → ahora es falso (porque interested[0] = 0)
✅ Entonces P1 entra al jardín 🌷
 * 
 * 
 * 
 */