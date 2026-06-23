#include "cola.h"
#include <stdio.h>
#include <stdlib.h>


Cola Cola_crear(){
    Cola cola = malloc(sizeof(struct _Cola));
    if(cola!=NULL){
        cola->inicio=NULL;
        cola->fin=NULL;
    }
    return cola;
}

int isEmpty(Cola cola){
    return cola==NULL || cola->inicio==NULL;
}

void * Tope(Cola cola){
    if (isEmpty(cola)) return NULL;
    
    return cola->inicio->dato;
}

Cola  Encolar(Cola cola, void * elemento, FuncionCopia copy){
    if (cola == NULL) return NULL;

    SNodo * nuevoNodo=malloc(sizeof(SNodo));
    nuevoNodo->dato=copy(elemento);
    nuevoNodo->sig=NULL;

    if(isEmpty(cola)){
        //no tiene datos
        cola->inicio=nuevoNodo;
        cola->fin=nuevoNodo;
        
        return cola;
    }

    cola->fin->sig=nuevoNodo;
    cola->fin=nuevoNodo; //actualizamos puntero.
    
    return cola;
}


Cola  Desencolar(Cola cola, FuncionDestructora destroy){
    if(isEmpty(cola)) return cola;

    SNodo * tmp= cola->inicio;
    cola->inicio=cola->inicio->sig;

    // si sacamos el ùltimo...!
    if(cola->inicio==NULL) cola->fin=NULL;

    destroy(tmp->dato);
    free(tmp);
    
    return cola;
}

Cola cola_destruir(Cola cola, FuncionDestructora destroy){
    if (cola == NULL) return NULL;

    while(!isEmpty(cola)){
        cola=Desencolar(cola,destroy);
    }

    free(cola);
    return NULL;
}

void cola_recorrer(Cola cola, FuncionVisitante fun){
    for(SNodo * tmp=cola->inicio;tmp!=NULL;tmp=tmp->sig){
        fun(tmp->dato);
    }
}

Cola cola_clonar(Cola original, FuncionCopia copy) {
    if (original == NULL) return NULL;
    
    Cola clon = Cola_crear();
    clon->inicio = snodo_copiar_recursivo(original->inicio, copy);
    
    // El único detalle de la Cola es que debemos reconectar el puntero 'fin'
    if (clon->inicio != NULL) {
        SNodo *tmp = clon->inicio;
        while (tmp->sig != NULL) {
            tmp = tmp->sig;
        }
        clon->fin = tmp;
    }
    
    return clon;
}


// Une la cola_extra al final de la cola1.
// La cola2 queda vacía.
Cola cola_unir_in_place(Cola cola1, Cola cola2) {
    if (isEmpty(cola1) || isEmpty(cola2)) {
        if(cola2->inicio!=NULL){
            cola1->inicio = cola2->inicio;
            cola1->fin = cola2->fin;
        }
        return cola1;
    }

    cola1->fin->sig = cola2->inicio;
    cola1->fin = cola2->fin; 

    cola2->inicio = NULL;
    cola2->fin = NULL;

    return cola1;
}



// Invierte el orden de la cola in-place, utilizando una Pila como buffer
void cola_revertir(Cola cola, FuncionCopia copy, FuncionDestructora destroy) {
    if (cola == NULL || isEmpty(cola)) return;

    Pila pila_aux = pila_crear();

    while (!isEmpty(cola)) {
        pila_aux=Push(pila_aux, Top(cola), copy);
        cola = Desencolar(cola, destroy);
    }

    while (!isEmpty(pila_aux)) {
        cola=Encolar(cola, Top(pila_aux), copy);
        pila_aux = Pop(pila_aux, destroy);
    }

    pila_aux=pila_destruir(pila_aux, destroy);
}

//retorna 1  si el elemento esta en la Cola, 0 si no.
int cola_contiene(Cola cola, void *dato_buscado, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(cola)) return 0;

    int encontrado = 0;
    Cola aux = Cola_crear();

    while (!isEmpty(cola)) {
        void *frente = Top(cola);
        if (comp(frente, dato_buscado) == 0) encontrado = 1;
    
        aux=Encolar(aux, frente, copy);
        cola = Desencolar(cola, destroy);
    }

    while (!isEmpty(aux)) {
        cola=Encolar(cola, Top(aux), copy);
        aux = Desencolar(aux, destroy);
    }

    aux=cola_destruir(aux, destroy);
    return encontrado;
}


// Elimina de la cola todos los elementos que cumplan el predicado,
// manteniendo el orden de los demás.
void cola_purgar_condicion(Cola cola, Predicado p, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(cola)) return;

    Cola aux = Cola_crear();

    while (!isEmpty(cola)) {
        void *frente = Top(cola);
        if (!p(frente)) { // Si NO falla, lo guardamos
            aux=Encolar(aux, frente, copy);
        }
        cola = Desencolar(cola, destroy);
    }

    // Volvemos a meter los sobrevivientes en la cola original
    while (!isEmpty(aux)) {
        cola=Encolar(cola, Top(aux), copy);
        aux = Desencolar(aux, destroy);
    }

    aux=cola_destruir(aux, destroy);
}


void cola_eliminar_duplicados(Cola cola, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(cola)) return;

    Cola aux = Cola_crear(); // Funciona como nuestro registro de elementos "únicos"

    while (!isEmpty(cola)) {
        void *frente = Top(cola);
        
        // Verificamos si ya guardamos este elemento en nuestra cola auxiliar
        if (!cola_contiene(aux, frente, comp, copy, destroy)) {
            aux=Encolar(aux, frente, copy);
        }
        cola = Desencolar(cola, destroy);
    }

    while (!isEmpty(aux)) {
        Encolar(cola, Top(aux), copy);
        aux = Desencolar(aux, destroy);
    }

    aux=cola_destruir(aux, destroy);
}

void cola_eliminar_duplicados_consecutivos(Cola cola, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(cola)) return;
    Cola aux = Cola_crear();

    while (!isEmpty(cola)) {
        
        if (isEmpty(aux) || comp(Top(aux), Top(cola)) != 0) {
            aux=Encolar(aux,  Top(cola), copy);
        }
        cola = Desencolar(cola, destroy);
    }

    while (!isEmpty(aux)) {
        cola=Encolar(cola, Top(aux), copy);
        aux = Desencolar(aux, destroy);
    }

    aux=cola_destruir(aux, destroy);
}


void cola_ordenar(Cola cola, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(cola)) return;

    Pila pila_temp = pila_crear();

    while (!isEmpty(cola)) {
        Push(pila_temp, Top(cola), copy);
        cola = Desencolar(cola, destroy);
    }

    pila_ordenar(pila_temp, comp, copy, destroy);

    while (!isEmpty(pila_temp)) {
        Encolar(cola, Top(pila_temp), copy);
        pila_temp = Pop(pila_temp, destroy);
    }

    pila_temp=pila_destruir(pila_temp, destroy);
}

Cola cola_racha_mas_larga(Cola cola, int n, Predicado p, FuncionCopia copy) {
    if (empty(cola) || n == 0) return crear_cola();

    int max_len = 0, mejor_inicio = -1;
    int actual_len = 0, actual_inicio = -1;

    // --- PRIMERA PASADA: Búsqueda del campeón (por índice) ---
    for (int i = 0; i < n; i++) {
        void *dato = tope(cola); // o primero(cola)

        if (p(dato)) {
            if (actual_len == 0) actual_inicio = i;
            actual_len++;

            if (actual_len > max_len) {
                max_len = actual_len;
                mejor_inicio = actual_inicio;
            }
        } else {
            actual_len = 0;
        }

        // Carrusel Fantasma (No gasta RAM)
        cola = encolar(cola, dato, no_copiar);
        cola = desencolar(cola, no_destruir);
    }

    // --- SEGUNDA PASADA: Construcción de la nueva cola ---
    Cola nueva = crear_cola();

    for (int i = 0; i < n; i++) {
        void *dato = tope(cola);

        // Si estamos parados adentro de los índices de la racha campeona
        if (max_len > 0 && i >= mejor_inicio && i < mejor_inicio + max_len) {
            // ACÁ SÍ USAMOS COPY REAL, porque 'nueva' es dueña de su propia memoria
            nueva = encolar(nueva, dato, copy); 
        }

        // Carrusel Fantasma
        cola = encolar(cola, dato, no_copiar);
        cola = desencolar(cola, no_destruir);
    }

    return nueva;
}

///========
// Función auxiliar para saber en qué índice está una letra
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
        if (dependencias_previas[i] == 0) Encolar(cola_listas, &nombres_tareas[i], copiar_char);
        
    }

    printf("Orden valido para realizar las tareas: ");
    int tareas_procesadas = 0;

    // Procesamos la fábrica
    while (!isEmpty(cola_listas)) {
        // Sacamos la tarea que está lista
        char tarea_actual = *(char *)Tope(cola_listas);
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