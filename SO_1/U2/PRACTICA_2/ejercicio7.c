// Ej. 7. Para la versi´on ingenua (sin exclusi´on m´utua) del jard´ın ornamental, ¿qu´e pasa cuando compilamos
// con optimizaciones? Pista: ver el assembler generado.

/*
En GCC, por ejemplo, las optimizaciones se activan con niveles usando la bandera -O:
- -O0 (Por defecto): No realiza optimizaciones (útil para depuración).
- -O1: Optimiza sin sacrificar mucho tiempo de compilación.
- -O2: Optimiza más agresivamente (código más rápido, pero mayor tiempo de compilación).
- -O3: Incluye optimizaciones adicionales como vectorización para mejorar aún más el rendimiento.
- -Os: Optimiza para reducir el tamaño del código.
*/

//Usa la bandera -S para pedir al compilador que genere el código ensamblador

// gcc ejercicio7.c -O3 -S -o ej6.out
//cat ej6.out

#include <stdio.h>
#include <pthread.h>

#define NUM_VISIT 200000
#define MOL_VISIT NUM_VISIT/2


int contador=0;

void * molinete1(void * arg){
    for(int x=0;x<MOL_VISIT;x++){
        contador++;
    }
    return NULL;

}

void * molinete2(void * arg){
    for(int x=0;x<MOL_VISIT;x++){
        contador++;
    }
    return NULL;

}

int main(){
    pthread_t m1,m2;

    pthread_create(&m1,NULL,molinete1,NULL);
    pthread_create(&m2,NULL,molinete2,NULL);

    pthread_join(m1,NULL);
    pthread_join(m2,NULL);

    printf("[Contador]: %d\n",contador);
    return 0;
}


/*
Compilar con optimizaciones (-O3) busca mejorar el rendimiento del programa, pero en tu caso, como no hay exclusión mutua, esto genera:
- Condiciones de carrera.
- Resultados incorrectos en la suma.
- Alteración del flujo esperado debido a optimizaciones agresivas.

ya que al reordenar las cosas para hacerlas más eficientes, las desordena de manera tal que elimina el for y lo reemplaza como una única instrucción , pero al hacer contador==100.000

*/

