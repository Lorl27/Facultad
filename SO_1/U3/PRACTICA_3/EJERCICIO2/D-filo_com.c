// Ej.2(Fil´osofos Comensales, Dijkstra).Cinco fil´osofos se sientan alrededor de una mesa redonda y viven la buena vida alternando entre comer y pensar.Cada fil´osofo tiene su plato de pasta, un tipo particular de fideos que requieren dos tenedores para ser comidos.Entre cada par de fil´osofos consecutivos hay un tenedor, y cada fil´osofo s´olo puede alcanzar los que est´an a su izquierda y derecha.Para comer, los fil´osofos acordaron primero tomar el tenedor a su derecha y luego el de a su izquierda.Si cualquier fil´osofo toma un tenedor y el otro est´a ocupado,
//     se quedar´a esperando, con un tenedor en la mano, hasta que pueda tomar el otro tenedor, para luego empezar a comer.Una vez que un fil´osofo terminar de comer deja los tenedores sobre la mesa y piensa hasta que le vuelve a dar hambre, cuando repite el procedimiento.Una implementaci´on de esta situaci´on con pthreads es como sigue :


// d) Un fil´osofo, ya sufriendo secuelas del hambre, sugiere que los comensales suelten su tenedor derecho
// si encuentran que el izquierdo ya est´a tomado, posiblemente esperando un tiempo antes de reintentar
// tomarlo. Implemente esta variante e invest´ıguela. ¿Funciona? ¿Es eficiente? Cuantifique su respuesta.

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
{   int exito=0;
    while(!exito){
        pthread_mutex_lock(der(i));

        if(pthread_mutex_trylock(izq(i))!=0){ //falló
            pthread_mutex_unlock(der(i));
            usleep(random() % ESPERA);
        }else{   //Obtuvo ambos ok
            exito=1;  
        }
    }
}
void dejar_tenedores(int i)
{
    pthread_mutex_unlock(der(i));
    pthread_mutex_unlock(izq(i));
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



/*


Sí. Esta solución evita el deadlock porque:

- Ningún filósofo se queda esperando indefinidamente con un solo tenedor.

- Siempre hay posibilidad de ceder el tenedor y que otro avance.

📉 ¿Es eficiente?
Depende. Tiene una desventaja clave: puede haber inanición (starvation):

Un filósofo puede tener mala suerte y siempre fallar en tomar el segundo tenedor.
En sistemas muy cargados, puede haber muchos reintentos → gasto de CPU innecesario.

📊 ¿Cómo cuantificar su eficiencia?
Podés hacer un experimento de simulación midiendo:

- ⏱️ Tiempo promedio de espera hasta que cada filósofo logra comer.

- 🍝 Número promedio de veces que un filósofo come en un intervalo de tiempo.

- 🔁 Cantidad de reintentos fallidos por filósofo.


*/