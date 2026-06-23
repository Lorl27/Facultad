#include "pila.h"
#include <stdio.h>
#include <stdlib.h>


Pila pila_crear(){
    Pila  pila = malloc(sizeof(struct _Pila));
    if(pila!=NULL){
        pila->inicio= NULL;
    }
    return pila;
}

int isEmpty(Pila  pila){
    return pila==NULL || pila->inicio == NULL;
}


void * Top(Pila pila){
    if(isEmpty(pila)) return NULL;

    return pila->inicio->dato;
}



Pila  Push(Pila  pila, void * elemento, FuncionCopia copy){
    if (pila == NULL) return NULL;

    SNodo * nuevo=malloc(sizeof(SNodo));
    nuevo->dato=copy(elemento);

    nuevo->sig=pila->inicio;
    pila->inicio=nuevo;

    return pila;
}

Pila  Pop(Pila  pila, FuncionDestructora destroy){
    if(isEmpty(pila)) return pila;

    SNodo * tmp = pila->inicio;
    pila->inicio=pila->inicio->sig;

    destroy(tmp->dato);
    free(tmp);

    return pila;
}


Pila pila_destruir(Pila pila, FuncionDestructora destroy){
    if (pila == NULL) return NULL;

    while (!isEmpty(pila)) {
        pila = Pop(pila, destroy);
    }
    free(pila);
    return NULL;
}

void pila_recorrer(Pila pila, FuncionVisitante fun){
    for(SNodo * tmp=pila->inicio;tmp!=NULL;tmp=tmp->sig){
        fun(tmp->dato);
    }
}


Pila pila_clonar(Pila original, FuncionCopia copy) {
    if (original == NULL) return NULL;
    
    Pila clon = pila_crear();
    clon->inicio = snodo_copiar_recursivo(original->inicio, copy);
    return clon;
}

// Une la pila2 DEBAJO de la pila1.
// La pila2 queda vacía estructuralmente.
Pila pila_unir_in_place(Pila pila1, Pila pila2) {
    if (isEmpty(pila1) || isEmpty(pila2)) {
        if (pila2 != NULL) {
            pila1->inicio = pila2->inicio;
            pila2->inicio = NULL;
        }
        return pila1; 
    }
    

    SNodo *tmp = pila1->inicio;
    while (tmp->sig != NULL) {
        tmp = tmp->sig;
    }

    tmp->sig = pila2->inicio;

    pila2->inicio = NULL;

    return pila1;
}


// Invierte el orden de la pila in-place, utilizando una Cola como buffer
void pila_revertir(Pila pila, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(pila)) return;

    Cola cola_aux = Cola_crear();

    while (!isEmpty(pila)) {
        cola_aux=Encolar(cola_aux, Top(pila), copy);
        pila = Pop(pila, destroy);
    }

    while (!isEmpty(cola_aux)) {
        pila=Push(pila, Top(cola_aux), copy);
        cola_aux = Desencolar(cola_aux, destroy);
    }

    cola_aux=cola_destruir(cola_aux, destroy);
}

//retorna 1  si el elemento esta en la pila, 0 si no.
int pila_contiene(Pila pila, void *dato_buscado, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(pila)) return 0;

    int encontrado = 0;
    Pila aux = pila_crear();

    while (!isEmpty(pila)) {
        void *tope = Top(pila);
        if (comp(tope, dato_buscado) == 0) encontrado = 1;
        
        aux=Push(aux, tope, copy);
        pila = Pop(pila, destroy);
    }

    while (!isEmpty(aux)) {
        aux=Push(pila, Top(aux), copy);
        aux = Pop(aux, destroy);
    }

    aux=pila_destruir(aux, destroy);
    return encontrado;
}

// Elimina de la pila todos los elementos que cumplan el predicado,
// manteniendo el orden de los demás.
void pila_purgar_condicion(Pila pila, Predicado p, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(pila)) return;

    Pila aux = pila_crear();

    while (!isEmpty(pila)) {
        void *tope = Top(pila);
        if (!p(tope)) { // Si NO cumple la condición de borrado, lo salvamos
            aux=Push(aux, tope, copy);
        }
        pila = Pop(pila, destroy); 
    }

    // Restauramos los sobrevivientes
    while (!isEmpty(aux)) {
        pila=Push(pila, Top(aux), copy);
        aux = Pop(aux, destroy);
    }
    aux=pila_destruir(aux, destroy);
}

/* la versin optima de memoria seria:
void pila_filtrar_destruyendo(Pila pila, FuncionFiltro debe_eliminarse, FuncionDestructora destroy_real) {
    if (pila == NULL || isEmpty(pila)) return;

    Pila aux = crear_pila();

    while (!isEmpty(pila)) {
        void *dato = Top(pila);

        if (debe_eliminarse(dato)) {
            // ELIMINACIÓN DEFINITIVA: Usamos el destroy real
            pila = Pop(pila, destroy_real); 
        } 
        else {
            // TRASLADO: Usamos las funciones fantasma
            aux = Push(aux, dato, no_copiar);
            pila = Pop(pila, no_destruir);
        }
    }

    // Restauramos los sobrevivientes a la pila original (giro estándar)
    while (!isEmpty(aux)) {
        pila = Push(pila, Top(aux), no_copiar);
        aux = Pop(aux, no_destruir);
    }

    aux = destruir_pila(aux, no_destruir);
}
*/

void pila_eliminar_duplicados(Pila pila, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(pila)) return;

    Pila aux = pila_crear(); // Funciona como registro de elementos "únicos"

    while (!isEmpty(pila)) {
        void *tope = Top(pila);
        
        // Si NO está en nuestra lista de únicos, lo agregamos
        if (!pila_contiene(aux, tope, comp, copy, destroy)) {
            aux=Push(aux, tope, copy);
        }
        pila = Pop(pila, destroy);
    }

    while (!isEmpty(aux)) {
        Push(pila, Top(aux), copy);
        aux = Pop(aux, destroy);
    }

    aux=pila_destruir(aux, destroy);
}

void pila_eliminar_duplicados_consecutivos(Pila pila, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(pila)) return;

    Pila aux = pila_crear();

    while (!isEmpty(pila)) {
        
        if (isEmpty(aux) || comp(Top(aux), Top(pila)) != 0) {
            aux=Push(aux, Top(pila), copy);
        }
        pila = Pop(pila, destroy); 
    }

    while (!isEmpty(aux)) {
        pila=Push(pila, Top(aux), copy);
        aux = Pop(aux, destroy);
    }

    aux=pila_destruir(aux, destroy);
}

void pila_ordenar(Pila pila, FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destroy) {
    if (isEmpty(pila)) return;

    Pila aux = pila_crear();

    while (!isEmpty(pila)) {
        void *tmp = copy(Top(pila));
        pila = Pop(pila, destroy);

        while (!isEmpty(aux) && comp(Top(aux), tmp) > 0) {
            pila=Push(pila, Top(aux), copy);
            aux = Pop(aux, destroy);
        }
        
        aux=Push(aux, tmp, copy);
        destroy(tmp);
    }

    while (!isEmpty(aux)) {
        pila=Push(pila, Top(aux), copy);
        aux = Pop(aux, destroy);
    }

    aux=pila_destruir(aux, destroy);
}


//la original se queda con los que cumplen p
// la nueva retorna los que no lo cumplen.
Pila pila_particionar(Pila pila, Predicado p) {
    if (isEmpty(pila)) return pila_crear();

    Pila aux_verdaderos = pila_crear();
    Pila aux_falsos = pila_crear();
    Pila nueva_falsos_final = pila_crear();

    while (!isEmpty(pila)) {
        void *dato = Top(pila);
        
        if (p(dato)) {
            aux_verdaderos = Push(aux_verdaderos, dato, no_copiar);
        } else {
            aux_falsos = Push(aux_falsos, dato, no_copiar);
        }
        
        pila = Pop(pila, no_destruir);
    }

    while (!isEmpty(aux_verdaderos)) {
        pila = Push(pila, Top(aux_verdaderos), no_copiar);
        aux_verdaderos = Pop(aux_verdaderos, no_destruir);
    }

    while (!isEmpty(aux_falsos)) {
        nueva_falsos_final = Push(nueva_falsos_final, Top(aux_falsos), no_copiar);
        aux_falsos = Pop(aux_falsos, no_destruir);
    }

    aux_verdaderos = destruir_pila(aux_verdaderos, no_destruir);
    aux_falsos = destruir_pila(aux_falsos, no_destruir);

    return nueva_falsos_final;
}

// Retorna una nueva pila con la segunda mitad (los elementos que estaban más arriba).
// La pila original queda modificada solo con la primera mitad (los que estaban más abajo).
Pila pila_partir(Pila pila, int n) {
    if (isEmpty(pila) || n <= 1) return pila_crear();

    int mitad = (n % 2 == 0) ? (n / 2) : (n / 2) + 1;
    Pila segunda_mitad_final = pila_crear();
    Pila aux_inversora = pila_crear();

    // 1. Volcamos TODO a la auxiliar para llegar al fondo
    // Orden actual en aux: [Fondo Pila Original ... Tope Pila Original] <- Tope aux
    while (!isEmpty(pila)) {
        aux_inversora = Push(aux_inversora, Top(pila), no_copiar);
        pila = Pop(pila, no_destruir);
    }

    // 2. Restauramos los primeros k elementos a la pila original
    // (Estos son la base/primera mitad, recuperan su orden correcto)
    for (int i = 0; i < mitad && !isEmpty(aux_inversora); i++) {
        pila = Push(pila, Top(aux_inversora), no_copiar);
        aux_inversora = Pop(aux_inversora, no_destruir);
    }

    // 3. El resto (la segunda mitad) va a la pila nueva definitiva.
    // Como los desapilamos de aux_inversora, también recuperan su orden relativo original.
    while (!isEmpty(aux_inversora)) {
        segunda_mitad_final = Push(segunda_mitad_final, Top(aux_inversora), no_copiar);
        aux_inversora = Pop(aux_inversora, no_destruir);
    }

    aux_inversora = destruir_pila(aux_inversora, no_destruir);

    return segunda_mitad_final;
}


Pila pila_racha_mas_larga(Pila pila, Predicado p, FuncionCopia copy) {
    if (pila == NULL || isEmpty(pila)) return pila_crear();

    int max_len = 0, mejor_inicio = -1;
    int actual_len = 0, actual_inicio = -1;
    int index = 0; // Contador desde el Tope original hacia el Fondo

    Pila aux = pila_crear();

    // --- PRIMERA PASADA: Vaciamos a la auxiliar tomando las medidas ---
    while (!isEmpty(pila)) {
        void *dato = Top(pila);

        if (p(dato)) {
            if (actual_len == 0) actual_inicio = index;
            actual_len++;

            if (actual_len > max_len) {
                max_len = actual_len;
                mejor_inicio = actual_inicio;
            }
        } else {
            actual_len = 0;
        }

        aux = Push(aux, dato, no_copiar);
        pila = Pop(pila, no_destruir);
        index++; 
    }

    // --- SEGUNDA PASADA: Restauración y Extracción ---
    Pila nueva = pila_crear();

    while (!isEmpty(aux)) {
        void *dato = Top(aux);
        
        // Al desapilar de aux, vamos desde el fondo hacia el tope.
        // Restamos el index para saber en qué posición original estamos parados.
        index--; 

        // Restauramos a la original
        pila = Push(pila, dato, no_copiar);

        // Si este índice pertenecía a la racha campeona
        if (max_len > 0 && index >= mejor_inicio && index < mejor_inicio + max_len) {
            // ACÁ SÍ USAMOS COPY REAL
            nueva = Push(nueva, dato, copy); 
        }

        aux = Pop(aux, no_destruir);
    }

    aux = destruir_pila(aux, no_destruir);
    return nueva;
}
//=================

GList Revertir_orden_lista_con_pila( GList lista, FuncionCopia copy, FuncionDestructora destroy){
    if (lista == NULL) return NULL;

    GList  nueva=slist_crear();
    Pila pila=pila_crear();
    SNodo *tmp = lista;

    while(tmp!=NULL){
        pila=Push(pila,&tmp->dato,copy);
        tmp=tmp->sig;
    }

    while(!isEmpty(pila)){
        int tope= copy(Top(pila));
        nueva=slist_agregar_final(nueva,tope);
        pila=Pop(pila,destroy);
    }

    pila=pila_destruir(pila,destroy);
    return nueva;
    
}

// por cada ( hay un )
int bien_parentizada(char expresion[]){
    if(expresion==NULL) return 0;

    Pila pila= pila_crear();
    for(int x=0;expresion[x]!='\0';x++){
        if(expresion[x] == '(') pila=Push(pila,&expresion[x],copiar_char);
        if(expresion[x] == ')') {
            if(isEmpty(pila)) {//no tiene su par.
                pila = pila_destruir(pila, (FuncionDestructora)destruir_char); 
                return 0; 
            } 
            pila=Pop(pila,(FuncionDestructora)destruir_char);
        }
    }

    int resultado=0;

    //cada parentesis deberia tener su par!
    if(isEmpty(pila)) resultado=1;

    pila=pila_destruir(pila,(FuncionDestructora)destruir_char);

    return resultado;
}

//---------------

int tiene_numeros(char caracter) {
    return caracter >= '0' && caracter <= '9';
}

// Ejecuta la cuenta y devuelve el resultado
int aplicar_operacion(int izq, int der, char op) {
    if (op == '+') return izq + der;
    if (op == '-') return izq - der;
    if (op == '*') return izq * der;
    if (op == '/') return izq / der;
    return 0;
}

// Devuelve el "peso" del operador (jerarquía)
int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // Para los paréntesis
}


// Función auxiliar que extrae y opera
void resolver_tope(Pila pila_numeros, Pila pila_operadores) {
    // Sacamos el operador
    char op = *(char*)Top(pila_operadores);
    Pop(pila_operadores, destruir_dato);

    // Sacamos el de la DERECHA primero
    int der = *(int*)Top(pila_numeros);
    Pop(pila_numeros, destruir_dato);

    // Sacamos el de la IZQUIERDA segundo
    int izq = *(int*)Top(pila_numeros);
    Pop(pila_numeros, destruir_dato);

    // Hacemos la cuenta
    int resultado = aplicar_operacion(izq, der, op);

    // Apilamos el resultado
    Push(pila_numeros, &resultado, copiar_enteros);
}

//------------------

int eval(char expr[]){
    if(expr==NULL) return 0;

    Pila pila_numeros=pila_crear();
    Pila pila_operadores=pila_crear();

    for(int x=0;expr[x]!='\0';x++){
        char c =expr[x];

        // Omitimos espacios en blanco por si acaso
        if(c != ' '){

            if(tiene_numeros(c)){
                int numero= c - '0';
                pila_numeros=Push(pila_numeros,&numero,copiar_enteros);
            }

            else if (c=='('){
                pila_operadores=Push(pila_operadores,&c,copiar_char);
            }

            
            else if (c==')'){
                // Resolvemos todo hasta chocar con el paréntesis abierto '('
                while(!isEmpty(pila_operadores) && *(char*)Top(pila_operadores) != '(') {
                    resolver_tope(pila_numeros, pila_operadores);
                }
                // Sacamos el '(' de la pila de operadores
                if(!isEmpty(pila_operadores)) {
                    pila_operadores=Pop(pila_operadores, destruir_dato);
                }
            }
            else { // Es un operador (+, -, *, /)
                // Mientras haya un operador en la pila con MAYOR O IGUAL jerarquía, lo resolvemos primero
                while(!isEmpty(pila_operadores) && precedencia(*(char*)Top(pila_operadores)) >= precedencia(c)){
                    resolver_tope(pila_numeros, pila_operadores);
                }
                // Finalmente, apilamos el operador actual
                Push(pila_operadores, &c, copiar_char);
            }
        }
    }

    // Al terminar de leer la palabra, resolvemos lo que haya quedado pendiente
    while(!isEmpty(pila_operadores)){
        resolver_tope(pila_numeros, pila_operadores);
    }

    int resultado=*(int*)Top(pila_numeros);
    pila_numeros=pila_destruir(pila_numeros,destruir_dato);
    pila_operadores=pila_destruir(pila_operadores,destruir_dato);

    return resultado;
}