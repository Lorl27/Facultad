#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *id_transaccion;
    double monto;
    int estado; // 0 = Pendiente, 1 = Aprobada, -1 = Rechazada
} Transaccion;

/*
Escribir las funciones transaccion_copia y 
transaccion_cmp_monto (que compara dos transacciones por su monto de mayor a menor) 

Implementar una función GList extraer_pendientes(GList *lista_original, FuncionCopia copy).
Esta función debe recorrer la lista_original.
Si encuentra una transacción con estado == 0 (Pendiente), 
debe desengancharla de la lista original y moverla a una nueva lista.
Retorna la nueva lista con todas las pendientes. 
¡Ojo! No se deben hacer copias físicas de los datos, solo se mueven los punteros GNode.
*/

void * transaccion_copia(void * t){
    Transaccion * trans_copia=malloc(sizeof(Transaccion));
    Transaccion * trans= (Transaccion *) t;
    trans_copia->estado=trans->estado;
    trans_copia->monto=trans->monto;
    trans_copia->id_transaccion=malloc(sizeof(char)*(strlen(trans->id_transaccion)+1));
    strcpy(trans_copia->id_transaccion,trans->id_transaccion);

    return trans_copia;
}

int transaccion_cmp_monto(void * t1, void * t2){
    Transaccion * trans1= (Transaccion *)t1;
    Transaccion * trans2= (Transaccion *)t2;

    if (trans2->monto > trans1->monto) return 1;
    if (trans2->monto < trans1->monto) return -1;
    return 0;
}

GList extraer_pendientes(GList *lista_original, FuncionCopia copy){
    if(*lista_original==NULL || lista_original==NULL) return NULL;

    GNode * nueva=NULL;
    GNode * prev=NULL;
    GNode * cola_nueva=NULL;
    GNode * inicio=*lista_original;
    while(inicio!=NULL){
        if(((Transaccion*)inicio->dato)->estado==0){

            GNode * tmp=inicio;
            inicio=inicio->sig;

            if(prev==NULL) *lista_original=inicio;
            else prev->sig=inicio;

            tmp->sig=NULL;

            if(nueva==NULL) nueva=tmp;
            else cola_nueva->sig=tmp;
            cola_nueva=tmp;

        }else{
            prev=inicio;
            inicio=inicio->sig;
        }
    }

    return nueva;

}

/*
Implementar la función void resolver_ruta(char directorios, int n).

La función recibe un arreglo de strings y su longitud n.

Debe procesar el arreglo en orden.
Si el string es un nombre normal (ej: "usr", "bin"), entra a la ruta.
Si el string es "..", retrocede una carpeta.

Al finalizar, debe imprimir la ruta definitiva.

$ resolver_ruta({"usr", "local", "..", "bin", "lib", "..", "share"}, 7)
usr
bin
share

// Explicación: Entra a usr -> local. El ".." saca a local. 
// Entra a bin -> lib. El ".." saca a lib. Entra a share.
Trampa de parcial: ¿Qué pasa si el arreglo es {"..", "usr"}?
 No puedes retroceder si estás en la raíz (pila vacía). 
 El código no debe explotar, simplemente ignora el ".." si no hay a dónde retroceder.
 */


void imprimir_pila(Pila pila){
    reverso(pila);
    while(!empty(pila)){
        printf("%s",(char*)tope(pila));
        pila = pop(pila);
    }
    printf("\n");
}

void resolver_ruta(char ** arr, int n){
    if(arr==NULL || n==0) return;

    Pila pila=pila_crear();

    for(int x=0;x<n;x++){
        if(strcmp("..",arr[x])!=0) pila=push(pila,arr[x]);
        else if(!empty(pila))pila=pop(pila);
    }

    imprimir_pila(pila);
    pila=destruir_pila(pila);
}


/*
Se pide:
Implementar la función void procesar_lote(Cola cola_queries, int quantum_tiempo, FuncionDestructora destroy).

La función atiende a la consulta que está al frente de la cola dándole quantum_tiempo milisegundos.

Si a la consulta le queda tiempo por procesar (milisegundos_restantes > quantum_tiempo),
 se le resta el tiempo usado y se la manda al final de la cola para que espere su próximo turno.

Si la consulta termina en ese turno (milisegundos_restantes <= quantum_tiempo),
 se imprime "Query X terminada" y se destruye el nodo definitivamente.

El ciclo continúa hasta que la cola quede completamente vacía.
*/

typedef struct {
    int query_id;
    int milisegundos_restantes;
} Query;

void procesar_lote(Cola cola_queries, int quantum_tiempo, FuncionDestructora destroy,FuncionCopia copy){
    if(empty(cola_queries)) return ;
    while(!empty(cola_queries)){
        Query * query_primera = (Query*)tope(cola_queries);
        
        if(query_primera->milisegundos_restantes>quantum_tiempo){
            query_primera->milisegundos_restantes-=quantum_tiempo;
            cola_queries=encolar(cola_queries,query_primera,copy);
        } 
        else {
            printf("Query nro %d terminada" , query_primera->query_id);
        }

        cola_queries=desencolar(cola_queries,destroy);
    }
}

/*
Se pide:
Implementar la función void procesar_transacciones(char consultas, int n).

La función recibe un arreglo de strings (consultas) y su tamaño n.

Debe usar una Pila para ir guardando el historial de consultas válidas.

Si el string es un nombre de consulta normal (ej: "INSERT_USER", "UPDATE_MAIL"), se apila.

Si el string es exactamente el comando "UNDO", se debe eliminar la última consulta apilada (si la pila no está vacía).

Si el string es exactamente el comando "ROLLBACK", la base de datos abortó la operación: 
la pila debe vaciarse por completo (quedar sin elementos, pero lista para seguir recibiendo datos).

Al finalizar el recorrido del arreglo, imprimir el historial definitivo desde el más antiguo al más reciente.
*/

void procesar_transacciones(char **consultas, int n){
    if(consultas==NULL || n==0) return;

    Pila pila = pila_crear();

    for(int x=0;x<n;x++){
        if(strcmp("UNDO",consultas[x])==0){
            if(!empty(pila)) pila=pop(pila,destroy);
        }
        else if(strcmp("ROLLBACK",consultas[x])==0) pila=vaciar_pila(pila,destroy);
        else{
            pila=push(pila,consultas[x],copy);
        }
    }

    imprimir_pila(pila);
    pila=pila_destruir(pila,destroy);
}


/*
Tienes una cola de procesos donde los elementos ingresaron,
 pero por un problema de latencia, los primeros K elementos llegaron en orden inverso y necesitas corregirlos.
  El resto de la cola está bien.
  Se pide:Implementar la función void invertir_k_elementos(Cola cola_procesos, int k, int n, FuncionCopia copy, FuncionDestructora destroy).
  n es la cantidad total de elementos actuales en la cola.
  k es la cantidad de elementos al frente de la cola que deben ser invertidos 
  Ejemplo conceptual:Si la Cola tiene [1, 2, 3, 4, 5] (donde 1 es el frente) y K = 3.
  El resultado final de la Cola debe ser [3, 2, 1, 4, 5].
*/

 void invertir_k_elementos(Cola cola_procesos, int k, int n, FuncionCopia copy, FuncionDestructora destroy){
    if(empty(cola_procesos)||k>n) return;

    Pila pila=pila_crear();
    
    for(int x=0;x<k;x++){
        pila=push(pila,tope(cola_procesos),copy);
        cola_procesos=desencolar(cola_procesos,destroy);
    }

    while(!empty(pila)){
        cola_procesos=encolar(cola_procesos,tope(pila),copy);
        pila=pop(pila,destroy);
    }

    for(int x=0;x<(n-k);x++){
        cola_procesos = encolar(cola_procesos, tope(cola_procesos), copy);
        cola_procesos=desencolar(cola_procesos,destroy);
    }

    pila=pila_destruir(pila,destroy);

 }

 /*
Se pide:Implementar la función void balancear_trafico(GList *lista_peticiones, Cola servidor_pesado, Cola servidor_liviano).
La función debe recorrer la lista genérica.
Si la petición tiene un peso_megabytes > 50, debe ser extraída de la lista y encolada en servidor_pesado.
Si tiene 50 o menos, debe ser extraída de la lista y encolada en servidor_liviano.
Al finalizar, la lista original lista_peticiones debe quedar apuntando a NULL (completamente vacía), 
pero no se debe utilizar free ni destruir los datos, ya que físicamente fueron trasladados a las colas.
 */

 typedef struct {
    char *endpoint;
    int peso_megabytes;
} PeticionHTTP;


void* no_copiar(void* dato) {
    return dato; 
}


void balancear_trafico(GList *lista_peticiones, Cola servidor_pesado, Cola servidor_liviano, FuncionCopiar copy){
    if(lista_peticiones==NULL || *lista_peticiones==NULL) return;

    GNode * inicio=*lista_peticiones;

    while(inicio!=NULL){
        PeticionHTTP * peticion = (PeticionHTTP *) inicio->dato;

        GNode * tmp=inicio;
            inicio=inicio->sig;

        if(peticion->peso_megabytes>50){
            servidor_pesado=encolar(servidor_pesado,tmp,no_copiar);
        }
        else {
            servidor_liviano=encolar(servidor_liviano,tmp,no_copiar);
        }
        free(tmp);

    }

    *lista_peticiones=NULL;
}


/*
Se tiene una Cola que almacena turnos médicos genéricos.
 Se necesita una función de mantenimiento que recorra la cola y
  elimine definitivamente a aquellos pacientes cuyo turno ya venció, conservando el orden original de los demás.

Reglas:
Si el elemento cumple la función debe_eliminarse, 
no vuelve a la cola y se debe liberar su memoria usando destruir.
La trampa: Tienes que asegurarte de no generar un bucle infinito.
 ¿Cómo sabes cuándo diste la vuelta completa a la cola
  si no puedes acceder a la cantidad de elementos internamente? (Hay una estrategia muy común para esto).
*/


// Retorna 1 si debe ser eliminado, 0 si debe conservarse
typedef int (*FuncionFiltro)(void *dato);
typedef void (*FuncionDestructora)(void *dato);

void cola_purgar(Cola c, FuncionFiltro debe_eliminarse, FuncionDestructora destruir, FuncionCopia copy){
    if(empty(c)) return;

    Cola aux= crear_cola();

    while(!empty(c)){
        if(!debe_eliminarse(tope(c))) aux=encolar(aux,tope(c),copy);
        c=desencolar(c,destruir);
    }

    while(!empty(aux)){
        c=encolar(c,tope(aux),copy);
        aux=desencolar(aux,destruir);
    }

    aux=destruir_cola(aux,destruir);
}



/*

La función debe crear y retornar una ÚNICA Cola final.

Debe procesar la lista_docs original. 
Todos los documentos urgentes deben quedar al principio de la cola devuelta, 
y los normales al final. 
(El orden relativo entre los urgentes debe mantenerse, igual que entre los normales).

Restricción: Puedes usar Colas auxiliares dentro de la función si las necesitas, pero al finalizar, 
la lista_docs original debe quedar apuntando a NULL y debes haber liberado sus GNode (las cajas), 
trasladando los datos a la Cola mediante la función copy.

*/

typedef struct {
    int id_documento;
    int paginas;
    int es_urgente; // 1 = Urgente, 0 = Normal
} Documento;


Cola planificar_impresiones(GList *lista_docs, FuncionCopia copy,FuncionDestructora destroy){
    if(lista_docs==NULL || *lista_docs==NULL) return NULL;

    Cola urgentes=crear_cola();
    Cola normal=crear_cola();
    Cola final=crear_cola();

    GNode * tmp=*lista_docs;
    while(tmp!=NULL){
        Documento * doc = (Documento *) tmp->dato;
        if(doc->es_urgente) urgentes=encolar(urgentes,doc,copy);
        else normal=encolar(normal,doc,copy);
        GNodo * eliminar=tmp;
        tmp=tmp->sig;
        free(eliminar);
    }

    while(!empty(urgentes)){
        final=encolar(final,tope(urgentes),copy);
        urgentes=desencolar(urgentes,destroy);
    }

    while(!empty(normal)){
        final=encolar(final,tope(normal),copy);
        normal=desencolar(normal,destroy);
    }

    normal=destruir_cola(normal,destroy);
    urgentes=destruir_cola(urgentes,destroy);

    *lista_docs=NULL;

    return final;
}


/*
Una secuencia es palíndroma si se lee igual de izquierda a derecha que de derecha a izquierda.
Retorna 1 si los elementos de la cola forman un palíndromo, o 0 si no lo hacen.

n es la cantidad de elementos en la cola.

La Trampa Mortal: Como es una función de consulta, la Cola original DEBE quedar en su estado y orden exacto original antes del return
(Pista: Para que la Pila te ayude a comparar, primero necesitas llenarla con el reverso de la Cola. Piensa cómo puedes hacer que la Cola dé un giro completo sobre sí misma mientras alimentas a la Pila).

*/
int cola_es_palindromo(Cola cola, int n, FuncionComparadora cmp, FuncionCopia copy, FuncionDestructora destroy){
    int es_palindromo=1;

    Cola cola_aux=copiar_cola(cola,copy);
    Pila pila=crear_pila();

    while(!empty(cola_aux)){
        pila=push(pila,tope(cola_aux),copy);
        cola_aux=desencolar(cola_aux,destroy);
    }

    while(!empty(pila)){
        if(cmp(tope(pila),tope(cola))!=0) es_palindromo=0;
        cola=encolar(cola,tope(pila),copy);
        pila=pop(pila,destroy);
        cola=desencolar(cola,destroy);
    }

    cola_aux=destruir_cola(cola_aux,destroy);
    pila=destruir_pila(pila,destroy);


    return es_palindromo;
}

//OTRA FORMA (COLA CARRUSEL)
int cola_es_palindromoV2(Cola cola, int n, FuncionComparadora cmp, FuncionCopia copy, FuncionDestructora destroy){
    if (empty(cola) || n <= 1) return 1;

    int es_palindromo = 1;
    Pila pila = crear_pila();

    // 1er Giro: Alimentamos la pila mientras la cola da la vuelta completa
    for (int i = 0; i < n; i++) {
        void *dato = tope(cola); // o primero(cola)
        pila = push(pila, dato, copy);
        
        // Carrusel: Sale del frente y entra al fondo
        cola = encolar(cola, dato, copy);
        cola = desencolar(cola, destroy);
    }

    // 2do Giro: Comparamos y restauramos
    for (int i = 0; i < n; i++) {
        void *dato_cola = tope(cola);
        void *dato_pila = tope(pila);

        // Si encontramos una diferencia, bajamos la bandera (pero NO hacemos break, 
        // debemos terminar el giro para no dejar la cola desarmada)
        if (cmp(dato_cola, dato_pila) != 0) {
            es_palindromo = 0;
        }

        pila = pop(pila, destroy);
        
        // Carrusel nuevamente
        cola = encolar(cola, dato_cola, copy);
        cola = desencolar(cola, destroy);
    }

    pila = destruir_pila(pila, destroy);
    return es_palindromo;
}

//=============

/*
El usuario puede ingresar tres tipos de cosas:

Una palabra normal (ej: "Hola", "Mundo"): Se apila.

El comando "BORRAR": Se desapila la última palabra ingresada (si la pila no está vacía).

El comando "DUPLICAR": Toma la palabra que está actualmente en el tope de la pila,
 y la apila de nuevo, duplicándola. (Si la pila está vacía, se ignora).

Al finalizar de procesar todo el arreglo de comandos,
 debes imprimir cómo quedó el texto (desde el fondo de la pila hasta el tope) separando las palabras con un espacio.


$ procesar_texto({"El", "perro", "BORRAR", "gato", "DUPLICAR", "corre"}, 6)
// Pila paso a paso:
// 1. "El"
// 2. "El", "perro"
// 3. "El" (por el BORRAR)
// 4. "El", "gato"
// 5. "El", "gato", "gato" (por el DUPLICAR)
// 6. "El", "gato", "gato", "corre"

Imprime: El gato gato corre
*/
void procesar_texto(char **comandos, int n, FuncionDestructora destroy, FuncionCopia copy){
    Pila pila=crear_pila();

    for(int x=0;x<n;x++){
        if(strcmp(comandos[x],"BORRAR")==0 && !empty(pila)) pila=pop(pila,destroy);
        else if(strcmp(comandos[x],"DUPLICAR")==0 && !empty(pila)) pila=push(pila,tope(pila),copy);
        else{
            pila=push(pila,comandos[x],copy);
        }
    }

    pila_imprimir(pila);
    pila=pila_destruir(pila,destroy);
}