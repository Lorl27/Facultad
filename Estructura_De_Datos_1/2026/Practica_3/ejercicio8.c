#include <stdio.h>
#include <stdlib.h>
#include "../Practica_3/Cola/cola.h"

void * copiar_char(void * caracter){
    char * copia = malloc(sizeof(char));
    *copia = *(char *)caracter;
    return copia;
}

void destruir_char(void * c){
    free(c);
}

// Función auxiliar para saber en qué índice (0 a cant_tareas-1) está una letra
int obtener_indice(char c, char tareas[], int cant_tareas) {
    for(int i = 0; i < cant_tareas; i++) {
        if(tareas[i] == c) return i;
    }
    return -1;
}


/* tmb podiamos haber hecho
typedef struct {
    char requisito; // Lo que hay que hacer primero
    char tarea;     // Lo que se destraba después
} Regla;

Regla listado_par_dependencias[]*/

void orden_valido_tareas(int cant_tareas,char nombres_tareas[], int num_deps,char listado_par_dependencias[][2]){
    // 1. Preparar los contadores (Grados de entrada) y el mapa (Matriz de adyacencia)
    int dependencias_previas[cant_tareas];
    int mapa[cant_tareas][cant_tareas];

    for (int i = 0; i < cant_tareas; i++) {
        dependencias_previas[i] = 0;
        for(int j = 0; j < cant_tareas; j++) {
            mapa[i][j] = 0;
        }
    }

    // 2. Llenar el mapa con las reglas del enunciado
    for (int i = 0; i < num_deps; i++) {
        int u = obtener_indice(listado_par_dependencias[i][0], nombres_tareas, cant_tareas); // Tarea A
        int v = obtener_indice(listado_par_dependencias[i][1], nombres_tareas, cant_tareas); // Tarea B
        
        mapa[u][v] = 1; // "u" debe ocurrir antes que "v"
        dependencias_previas[v]++; // "v" ahora tiene un requisito más antes de poder empezar
    }

    // 3. ¡Arranca el Algoritmo con la Cola!
    Cola cola_listas = Cola_crear();

    // Metemos a la cola las tareas que no dependen de nadie (dependencias == 0)
    for (int i = 0; i < cant_tareas; i++) {
        if (dependencias_previas[i] == 0) {
            Encolar(cola_listas, &nombres_tareas[i], copiar_char);
        }
    }

    printf("Orden valido para realizar las tareas: ");
    int tareas_procesadas = 0;

    // Procesamos la fábrica
    while (!isEmpty(cola_listas)) {
        // Sacamos la tarea que está lista
        char tarea_actual = *(char *)cola_listas->inicio->dato;
        printf("%c ", tarea_actual);
        Desencolar(cola_listas, destruir_char);
        
        tareas_procesadas++;
        int indice_actual = obtener_indice(tarea_actual, nombres_tareas, cant_tareas);

        // Avisamos a las demás tareas que ya terminamos esta
        for (int i = 0; i < cant_tareas; i++) {
            if (mapa[indice_actual][i] == 1) {
                // Le restamos una dependencia a la tarea 'i'
                dependencias_previas[i]--; 
                
                // Si la tarea 'i' ya no debe esperar a nadie más, ¡a la cola!
                if (dependencias_previas[i] == 0) {
                    Encolar(cola_listas, &nombres_tareas[i], copiar_char);
                }
            }
        }
    }
    printf("\n");

    // Detalle de seguridad: Si no logramos hacer todas las tareas, ¡hay un ciclo imposible! (Ej: A pide B, y B pide A)
    if (tareas_procesadas != cant_tareas) {
        printf("ALERTA: Es imposible terminar. Hay dependencias circulares.\n");
    }

    cola_destruir(cola_listas, destruir_char);
}


// ========================================================
int main() {
    // Los datos del enunciado
    int cant_tareas = 5;
    char tareas[] = {'A', 'B', 'C', 'D', 'E'};
    
    int num_deps = 5;
    char dependencias[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'C', 'E'},
        {'A', 'D'},
        {'D', 'E'}
    };

    orden_valido_tareas(cant_tareas, tareas, num_deps, dependencias);

    return 0;
}