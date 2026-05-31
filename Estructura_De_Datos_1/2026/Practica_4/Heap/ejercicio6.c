#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"



// Un enum es ideal para manejar estados concretos
typedef enum { APROBADO, RECUPERA, REGULAR, LIBRE } Condicion;

typedef struct _Estudiante {
    // --- Datos de Información ---
    char nombre[50];
    int legajo;
    
    // --- Datos de Prioridad ---
    Condicion condicion;
    int tiempo_llegada; // Para facilitar, expresado en minutos desde las 00:00 (ej: 8:30am = 510)
} Estudiante;



int obtener_hora_actual_en_minutos(); // Función hipotética del sistema


//A>b : 1  (en contexto de prioridad)
// A<B : -1
// A==B : 0
int comparar_prioridad_estudiantes(void * a, void * b) {
    Estudiante * est_a = (Estudiante *)a;
    Estudiante * est_b = (Estudiante *)b;

    int hora_actual = obtener_hora_actual_en_minutos();
    int limite_10am = 10 * 60; // 600 minutos

    // REGLA 1: Antes de las 10am, los de 'Recupera' tienen prioridad absoluta
    if (hora_actual < limite_10am) {
        if (est_a->condicion == RECUPERA && est_b->condicion != RECUPERA) {
            return 1; // A tiene mayor prioridad
        }
        if (est_b->condicion == RECUPERA && est_a->condicion != RECUPERA) {
            return -1; // B tiene mayor prioridad
        }
    }

    // REGLA 2: Después de las 10am, o si empatan en condición (ambos recuperan o ninguno),
    // la prioridad la define la hora de llegada.
    
    // El que tiene MENOR tiempo de llegada (llegó antes), tiene MAYOR prioridad
    if (est_a->tiempo_llegada < est_b->tiempo_llegada) return 1;
    if (est_a->tiempo_llegada > est_b->tiempo_llegada) return -1;

    return 0; // Llegaron exactamente al mismo tiempo
}


/*
c) La estructura de datos adecuadaLa respuesta correcta y de manual es:
 Una Cola de Prioridad implementada internamente mediante un Heap Binario.
 
 Justificación para tu examen:
 El problema requiere manejar un flujo dinámico de estudiantes que llegan (inserciones) y que son atendidos por el profesor (extracción del "máximo" prioritario).
 Un Heap Binario permite realizar tanto la inserción como la extracción del elemento más prioritario en tiempo logarítmico $O(\log n)$, 
 lo cual es inmensamente más eficiente que mantener un arreglo/lista ordenado (que costaría $O(n)$ por inserción) o buscar en uno desordenado (que costaría $O(n)$ por extracción).
*/

/*
¿Qué pasa exactamente a las 10:00 AM con el Heap?
Un Heap mantiene su estructura en base a una función comparadora estática. Si tienes un montón de estudiantes esperando en el Heap a las 9:59 AM (ordenados con los de 'Recupera' en la cima), y el reloj marca las 10:00 AM... ¡La regla comparadora acaba de cambiar!
Automáticamente, el Heap queda invalidado porque los elementos ya no están ordenados según la nueva regla (que ahora solo mira la hora de llegada).

Para que el programa funcione en la vida real, a las 10:00 AM en punto deberíamos ejecutar el algoritmo de Heapify (el que programaste en el Ejercicio 3) sobre el arreglo interno de la Cola de Prioridad para reordenarlos a todos de golpe en tiempo O(n) con la nueva lógica.
*/