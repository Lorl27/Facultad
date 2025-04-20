// Ej. 6. Considere el problema del jard´ın ornamental en un sistema con un ´unico procesador.
// a) ¿Sigue habiendo un problema? Justifique.
// b) Si implementa el algoritmo de Peterson, ¿son necesarias las barreras de memoria?
// c) Si el incremento se hace con la instrucci´on incl de x86, ¿hay problema? Puede aprovechar la
// siguiente funci´on:
// static inline void incl(int *p) {
// asm("incl %0" : "+m"(*p) : : "memory");
// }
// d) ¿Qu´e pasa con la implementaci´on con incl al tener m´as de un procesador?
// e) Repita el experimento con esta versi´on de incl:
// static inline void incl(int *p) {
// asm("lock; incl %0" : "+m"(*p) : : "memory");
// }

//----------A:
/* No, el problema prácticamente desaparece en un sistema de un único procesador, porque:
- Contexto de un único procesador:- Solo un hilo o proceso puede ejecutarse a la vez. Si un hilo está en la región crítica, el otro debe necesariamente esperar su turno, ya que el sistema no permite que ambos se ejecuten simultáneamente.

- Exclusión implícita:- El sistema operativo asegura una exclusión "implícita" al cambiar de contexto entre hilos o procesos, ya que estos no pueden ejecutarse físicamente al mismo tiempo.
*/

//----B:
/* No, por lo del A  + no existe concurrencia. */

//--C:
/* En sistemas de un único procesador no se rompe, pero en más de uno sí.
La instrucción incl es atómica en un único procesador, ya que no puede ser interrumpida para ejecutar otro hilo.
*/


//---D:
//Si hay problemas, el contador a veces no llega al valor que debe llegar por hasta -9 valores atrás(Race condition al no tener lock)

//--E:
// Al poseer lock, ahora anda bien todo =)

#include <stdio.h>
#include <pthread.h>

#define NUM_VISIT 200000
#define MOL_VISIT NUM_VISIT/2

static inline void incl1(int *p) {
    asm("incl %0" : "+m"(*p) : : "memory");
}

static inline void incl2(int *p) {
    asm("lock; incl %0" : "+m"(*p) : : "memory");
}

int flags[2]={0};  //flag[]=1 quiero ir , flags[]=0 no quieor ir.
int turno=0;  //0: puedo ir

int contador=0;

void * molinete1(void * arg){
    for(int x=0;x<MOL_VISIT;x++){
        flags[0]=1;
        turno=2;
        while(flags[1]==1 && turno==2){
            ; //espera activa
        }

        //contador++;
        //incl1(&contador);
        incl2(&contador);

        flags[0]=0;
    }
    return NULL;

}

void * molinete2(void * arg){
    for(int x=0;x<MOL_VISIT;x++){
        flags[1]=1;
        turno=1;
        while(flags[0]==1 && turno==1){
            ; //espera activa
        }

        //contador++;
        //incl1(&contador);
        incl2(&contador);

        flags[1]=0;
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


/* *NOTE - 
EXPLICACIÓN DE incl2 (por IA):
Utiliza ensamblador en línea para realizar una operación de incremento sobre un puntero a un entero (`int *p`) en C, con una sincronización especial para garantizar exclusión mutua en sistemas multiprocesador.

### **Desglose de lo que hace:**
#### 1. **`static inline`**:
   - `static`: Limita la función `incl2` al archivo donde se define, evitando conflictos con otras partes del programa.
   - `inline`: Indica al compilador que puede integrar el código de la función directamente en el lugar donde se llama, evitando una llamada a función tradicional (por eficiencia).

#### 2. **Ens ensamblador (`asm`)**:
   - El código usa la instrucción ensamblador de arquitectura x86 para modificar el valor de la variable apuntada por `p`.

#### 3. **`lock`**:
   - La palabra clave `lock` en ensamblador x86 asegura que la operación sea atómica en sistemas multiprocesador.
   - Específicamente, evita que otros procesadores accedan a la misma variable (`p`) mientras se realiza el incremento, bloqueando el acceso a esta región de memoria.
   - Esto garantiza coherencia en los accesos a la memoria compartida en sistemas con más de un núcleo.

#### 4. **`incl %0`**:
   - `incl` es la instrucción de ensamblador para incrementar el valor de una variable.
   - Aquí incrementa el valor almacenado en la dirección de memoria referenciada por `%0`.

#### 5. **`: "+m"(*p)`**:
   - `"+m"` indica que `*p` es un operando **modificable**. Se pasa como referencia de memoria para que el ensamblador trabaje directamente con él.
   - Esto significa que el valor en la dirección de memoria apuntada por `p` será leído y luego sobrescrito con el valor incrementado.

#### 6. **`: : "memory"`**:
   - Indica que la operación afecta directamente la memoria. El ensamblador asegura que no se produzcan optimizaciones que puedan ignorar o reordenar los accesos a memoria relacionados con esta operación.


### **Resumen funcional:**
La función `incl2` incrementa el valor de la dirección apuntada por `p` y asegura que el incremento sea:
1. Atómico: Ningún otro proceso o hilo puede modificar la variable mientras se realiza el incremento.
2. Visible: La sincronización asegura que el cambio en memoria sea consistente entre los procesadores.

Este enfoque es útil para operaciones que deben ser seguras en un entorno concurrente, como en sistemas operativos o programas multihilo.
*/