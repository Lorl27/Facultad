// Ej. 8. En la siguiente implementaci´on del jard´ın ornamental (asumiendo dos molinetes), agregue
// estrat´egicamente algunos sleep() para obtener el m´ınimo valor posible de visitantes. Puede usar
// condicionales.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int visitantes=0;

#define NUM_VISIT 200000
#define N NUM_VISIT/2


void * proc(void *arg) {
    int i;
    int id = arg - (void*)0;
    for (i = 0; i < N; i++) {
        int c;
        /* sleep? */
        c = visitantes;
        sleep(0.000001);
        visitantes = c + 1;
        /* sleep? */
    }
    return NULL;
}


int main(){
    pthread_t m1,m2;

    pthread_create(&m1,NULL,proc,NULL);
    pthread_create(&m2,NULL,proc,NULL);

    pthread_join(m1,NULL);
    pthread_join(m2,NULL);

    printf("[Contador]: %d\n",visitantes);
    return 0;
}