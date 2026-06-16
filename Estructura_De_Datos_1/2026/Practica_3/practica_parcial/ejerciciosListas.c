#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;


typedef void * (*FuncionCopia)(void * dato);
typedef void (*FuncionDestructora)(void * dato);
typedef void (*FuncionVisitante)(void * dato);
typedef void * (*FuncionTransformar)(void * dato);
typedef int (*FuncionComparadora)(void * dato, void* dato2);

//================

typedef struct {
    char *codigo;
    char *departamento;
    int sueldo;
} Empleado;



/*Debe realizar una copia física profunda (deep copy) del empleado. */
void *empleado_copia(void *dato);
/*Implementar empleado_comparar_sueldo: Para ordenar la lista de Mayor a Menor sueldo.*/
int empleado_comparar_sueldo(void *a, void *b);
/*Escribir un Predicado llamado es_de_ventas que retorne 1 si el empleado pertenece al departamento "Ventas" y 
0 en caso contrario.*/
int es_de_ventas(void *dato);

void *empleado_copia(void *dato){
    Empleado * e=(Empleado * )dato;
    Empleado * empleado=malloc(sizeof(Empleado));
    empleado->sueldo=e->sueldo;

    empleado->codigo=malloc(sizeof(char)*(strlen(e->codigo)+1));
    strcpy(empleado->codigo,e->codigo);

    empleado->departamento=malloc(sizeof(char)*(strlen(e->departamento)+1));
    strcpy(empleado->departamento,e->departamento);

    return empleado;
}

int empleado_comparar_sueldo(void *a, void *b){
    Empleado *emp_a = (Empleado *)a;
    Empleado *emp_b = (Empleado *)b;
    return emp_b->sueldo - emp_a->sueldo;
}

int es_de_ventas(void *dato){
    Empleado * e=(Empleado *) dato;
    return (strcmp(e->departamento, "Ventas") == 0 || strcmp(e->departamento, "ventas") == 0 || strcmp(e->departamento, "VENTAS") == 0);
}


///===============

//lista doblemente enlazada
typedef struct nodoD {
    int dato;
    struct nodoD *ant;
    struct nodoD *sig;
} NodoD;
typedef NodoD *DList;


/*
Tu tarea: 
Escribir una función que recorra la lista doble y elimine todos los nodos que contengan números impares.

Regla de Oro: Cuidado al borrar.
 Tienes que reconectar correctamente el ant y el sig de los nodos vecinos al nodo que vas a borrar.

Regla de Platino: ¡Ojo con el caso en que el nodo a borrar sea el primero (la cabeza) de la lista!
 Tendrás que actualizar el inicio, por eso recibes un DList *.
*/
void dlist_eliminar_impares(DList *lista){
    if(lista==NULL || *lista == NULL) return;

    NodoD * tmp=*lista;

    while(tmp!=NULL){
        if(tmp->dato%2!=0){
            NodoD * temporal = tmp;
            NodoD * temporal_ant = tmp->ant;
            tmp=tmp->sig;
            if(temporal_ant==NULL) *lista=tmp;
            else temporal_ant->sig=tmp;

            if(tmp!=NULL) temporal_ant=tmp->ant;
            free(temporal);
        }
        else tmp=tmp->sig;
    }

    
}


//===============
typedef struct {
    char *username; // ej: "juanperez"
    char *dominio;  // ej: "gmail.com"
} Email;


/*implementar*/
void *email_copia(void *dato);
/*Escribir un Predicado llamado es_dominio_oficial que retorne 1 si el dominio es exactamente "unr.edu.ar" o "fceia.unr.edu.ar".*/
int es_dominio_oficial(void *dato);
/*Implementar la función principal glist_filtrar_oficiales que reciba una lista de Emails y
 retorne una NUEVA lista conteniendo solo los correos oficiales, usando copias físicas.*/
GList glist_filtrar_oficiales(GList lista); 


void * email_copia(void * dato){
    Email * e = (Email * )dato;
    Email * copia = malloc(sizeof(Email));
    copia->dominio=malloc(sizeof(char)*(strlen(e->dominio)+1));
    strcpy(copia->dominio,e->dominio);

    copia->username=malloc(sizeof(char)*(strlen(e->username)+1));
    strcpy(copia->username,e->username);

    return copia;
}


int es_dominio_oficial(void *dato){
    Email * e= (Email *)dato;
    return strcmp(e->dominio,"unr.edu.ar")==0 || strcmp(e->dominio,"fceia.unr.edu.ar")==0;
}


GList glist_filtrar_oficiales(GList lista){
    GList new= glist_crear(); 
    for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
        if(es_dominio_oficial(tmp->data)) new=insertar_al_inicio(new,tmp->data,email_copia);
    }
    return new;
}




//=============


typedef struct {
    int id_transaccion;
    char *modulo;  // ej: "Inventario", "Facturacion"
    char estado;   // 'E' para Error, 'O' para OK
} Transaccion;

void *transaccion_copia(void *dato){
    Transaccion * e=(Transaccion * )dato;
    Transaccion * transaccion=malloc(sizeof(Transaccion));
    transaccion->id_transaccion=e->id_transaccion;

    transaccion->modulo=malloc(sizeof(char)*(strlen(e->modulo)+1));
    strcpy(transaccion->modulo,e->modulo);

    transaccion->estado = e->estado;

    return transaccion;
}
/*
Implementar glist_extraer_errores. 
Esta función recibe la lista original, la recorre, y devuelve una NUEVA lista que 
contenga solo las transacciones cuyo estado sea 'E'. La lista original no se toca en absoluto.
*/
GList glist_extraer_errores(GList lista_original){
    GList nueva= glist_crear();
    for(GNode * tmp=lista_original;tmp!=NULL;tmp=tmp->next){
        if(((Transaccion *)tmp->data)->estado=='E'||((Transaccion *)tmp->data)->estado=='e') nueva=insertar_al_final(nueva,tmp->data,transaccion_copia);
    }
    return nueva;
}




//===============

/*
Tienes una lista general que almacena consultas a la base de datos (Strings puros: char *). 
Necesitas un "enrutador" que lea la lista original y la divida en dos listas nuevas: 
una para consultas de lectura (que empiezan con "SELECT") 
y otra para escritura (que empiezan con "UPDATE" o "INSERT").

Tu tarea:
Implementar glist_clasificar_consultas.

Recibe la lista original intacta.

Recibe dos punteros por referencia (GList *lista_lectura, GList *lista_escritura) 
donde deberás construir las dos listas nuevas.
*/
void glist_clasificar_consultas(GList lista_original, GList *lista_lectura, GList *lista_escritura){
    if(lista_original==NULL){
        *lista_escritura=NULL;
        *lista_lectura=NULL;
        return;
    }

    for(GNode * tmp=lista_original;tmp!=NULL;tmp=tmp->next){
        if(strncmp(tmp->data,"SELECT",6)==0) *lista_lectura=agregar_al_inicio(*lista_lectura,tmp->data,no_copiar);
        else if(strncmp(tmp->data,"UPDATE",6)==0 || strncmp(tmp->data,"INSERT",6)==0 ) *lista_escritura=agregar_al_inicio(*lista_escritura,tmp->data,no_copiar);
    }
}


//==================

/*
Tu tarea: Recibes una lista original, un dato "pivote" y dos punteros a listas vacías (menores y mayores_iguales). 
Debes recorrer la lista original y copiar físicamente los datos a la lista que corresponda.

Si el dato es menor al pivote, va a la lista menores.

Si es mayor o igual, va a la lista mayores_iguales.
*/
void glist_split_pivote(GList original, void *pivote, FuncionComparadora cmp, FuncionCopia copy, GList *menores, GList *mayores_iguales){
    if(original==NULL){
        *menores=NULL;
        *mayores_iguales=NULL;
        return;
    }

    for(GNode * tmp=original;tmp!=NULL;tmp=tmp->next){
        if(cmp(tmp->data,pivote)<0){
            *menores=agregar_al_inicio(*menores,tmp->data,copy);
            
        }else{
            *mayores_iguales=agregar_al_inicio(*mayores_iguales,tmp->data,copy);
        }
    }

    *menores = reverso(*menores, copy);
    *mayores_iguales = reverso(*mayores_iguales, copy);
}


///========
typedef GNode *CList; // Lista circular simple

/*
Imagina que recibes un puntero a un nodo cualquiera dentro de una Lista Circular Simplemente Enlazada (CList).

Tu tarea: Implementar una función que recorra esa lista circular,
 extraiga copias físicas de los datos que cumplan con un Predicado, y
  los guarde en una Lista Lineal Normal (GList).
*/
GList clist_a_glist_filtrada(CList circular, Predicado p, FuncionCopia copy){
    GList nueva=glist_crear();
    if(circular==NULL) return nueva;

    GNode * inicio=circular;

    do{
        if(p(inicio->data)){
            nueva=insertar_al_inicio(inicio->data,copy);
        }
        inicio=inicio->next;
    }while(inicio!=circular);

    return nueva;
}


//===============

/*
Tienes una lista general (GList) donde cada dato almacenado es otra GList. (Una lista de listas).
Tu tarea: Implementar glist_aplanar. 
Debes crear una ÚNICA lista plana y nueva que contenga todos los elementos individuales de todas las sub-listas, 
en el orden en que aparecen.

Ejemplo: [[1, 2], [3], [4, 5]]  -> [1, 2, 3, 4, 5]

Regla de Oro: Necesitas un doble bucle (o un bucle y llamadas a funciones auxiliares). 
Debes hacer copy de cada dato individual.

Pista del compilador: 
Para acceder a la sub-lista dentro del nodo principal, tendrás que castear el void *data a un GList.
*/
GList glist_aplanar(GList lista_de_listas, FuncionCopia copy_dato_individual){
    if(lista_de_listas==NULL) return NULL;
    GList lista=glist_crear();

    for(GNode * principal=lista_de_listas;principal!=NULL;principal=principal->next){
        for(GNode * sublista= (GNode *)principal->data;sublista!=NULL;sublista=sublista->next){
            lista=insertar_al_final(lista,sublista->data,copy_dato_individual);
        }
    }

    return lista;
}

//===========
typedef struct {
    char *dni;
    char *nombre_completo;
} Persona;

typedef struct {
    char *dni;
    float monto_deuda;
} Multa;

typedef struct {
    char *nombre_completo;
    float monto_deuda;
} Deudor; // La estructura resultante


/*
Recibes la lista de Personas y la lista de Multas.
Debes devolver una NUEVA lista de tipo Deudor.

Por cada Multa, debes buscar a la Persona correspondiente
 (con el mismo DNI) en la lista de personas.

Si la encuentras, fabricas un Deudor 
(haciendo los malloc correspondientes para sus campos) y 
lo insertas en la nueva lista.
*/

void * copiar_char(void * c){
    char * char_c = malloc(sizeof(char));
    char * c_char = *(char * )c;
    * char_c=*c_char;
    return char_c;
}

GList glist_generar_deudores(GList lista_personas, GList lista_multas){
    if(lista_personas==NULL || lista_multas==NULL ) return NULL;

    GNode * lista_deudas=glist_crear();

    for(GNode * tmp=lista_multas;tmp!=NULL;tmp=tmp->next){
        for(GNode * per=lista_personas;per!=NULL;per=per->next){
            Persona * p= (Persona *) per->data;
            Multa * m = (Multa *) tmp->data;
            if(strcmp(m->dni,p->dni)==0){
                Deudor * deudor=malloc(sizeof(Deudor));
                deudor->monto_deuda=m->monto_deuda;
                
                deudor->nombre_completo=malloc(sizeof(char)*(strlen(p->nombre_completo)+1));
                strcpy(deudor->nombre_completo,p->nombre_completo);

                lista_deudas=agregar_al_inicio(lista_deudas,deudor,no_copiar);
            }
        }
    }
    return lista_deudas;
}

///=============
/*
Recibes el arreglo de listas (arr[0]=lista1), el tamaño del arreglo, 
y debes devolver una ÚNICA NUEVA LISTA que contenga todos los elementos de todas 
las listas del arreglo, ordenados de menor a mayor.

Regla de Oro: Las listas originales dentro del arreglo no se tocan.
*/
GList glist_fusionar_arreglo(void **arreglo_listas, int num_listas, FuncionCopia copy, FuncionComparadora cmp){
    if(arreglo_listas==NULL || num_listas==0) return NULL;
    
    GList new = glist_crear();

    for(int x=0; x<num_listas-1;x++){
        for(GNode * lista=(GNode *)arreglo_listas[x];lista!=NULL;lista=lista->next){
            new=insertar_ordenado(new,lista->data,copy,cmp);
        }
    }
    return new;
}


//====================
typedef struct {
    char *titulo;
    int *id_editores;    // Un arreglo dinámico de enteros con los IDs de quienes editaron
    int cant_editores;   // Cuántos editores hay en el arreglo
} Documento;



void *documento_copia_profunda(void *dato){
    Documento * doc = (Documento *) dato;
    Documento * copia = malloc(sizeof(Documento));
    copia->cant_editores=doc->cant_editores;
    copia->titulo=malloc(sizeof(char)*(strlen(doc->titulo)+1));
    strcpy(copia->titulo,doc->titulo);

    copia->id_editores=malloc(sizeof(int)*doc->cant_editores);
    for(int x=0;x<doc->cant_editores;x++){
        copia->id_editores[x]=doc->id_editores[x];
    }

    return copia;

}


/*
Recibe una lista original de documentos y devuelve una NUEVA lista 
(usando tu copia profunda)
 solo con los documentos que hayan sido editados por más de 3 personas 
 (cant_editores > 3).
*/
GList glist_clonar_documentos_editados(GList lista_original){
    if(lista_original==NULL) return NULL;
    GList new= glist_crear();

    for(GNode * tmp=lista_original;tmp!=NULL;tmp=tmp->next){
        Documento * d= (Documento *) tmp->data;
        if(d->cant_editores>3) new=insertar_al_inicio(new,d,documento_copia_profunda);
    }

    return new;
}


//============0
/* devolver elementos A-B ( que esten en A y NO en B)*/
GList glist_diferencia(GList lista_A, GList lista_B, FuncionComparadora cmp, FuncionCopia copy){
    if(lista_A==NULL) return NULL;
    
    GList new= glist_crear();

    for(GNode * tmp=lista_A;tmp!=NULL;tmp=tmp->next){
        if(!contiene(lista_B,tmp->data,cmp) && !contiene(new,tmp->data,cmp)) new=insertar_ordenado(new,tmp->data,copy,cmp);
    }

    return new;
}


//================

/*
 La operación Zip es distinta: toma el primer elemento de A y el primero de B, los fusiona en un solo dato nuevo usando una función especial, 
 y guarda ese dato en la lista resultante.Ejemplo conceptual: Si A = [1, 2, 3] y B = [10, 20, 30], 
 y la función combinadora los suma, el resultado es [11, 22, 33].Tu tarea: Recorrer ambas listas a la vez. 
 Aplicar FuncionCombinar a los datos que están en la misma posición. Guardar el resultado en una nueva lista.
 Regla de Oro: Si una lista es más corta que la otra, el proceso se detiene en cuanto
  la más corta se termina (los elementos sobrantes de la más larga se ignoran).
  Regla de Platino: La FuncionCombinar ya se encarga de hacer el malloc del nuevo dato, así que no necesitas una FuncionCopia extra.
*/
// Retorna un nuevo dato (void*) creado a partir de a y b
typedef void *(*FuncionCombinar)(void *a, void *b);

// Función auxiliar obligatoria para no duplicar la memoria que ya nos dio 'comb'
void *no_copiar(void *dato) {
    return dato;
}

GList glist_zip(GList lista_A, GList lista_B, FuncionCombinar comb) {
    GList nueva = glist_crear(); 
    
    GNode *tmpA = lista_A;
    GNode *tmpB = lista_B;

    // El bucle corta naturalmente en cuanto UNA de las dos listas llegue a NULL
    while (tmpA != NULL && tmpB != NULL) {
        // 1. Fabricamos el dato fusionado
        void *dato_fusionado = comb(tmpA->data, tmpB->data);
        
        // 2. Lo insertamos (uso tu insertar_al_final preferido)
        nueva = insertar_al_final(nueva, dato_fusionado, no_copiar);
        
        // 3. Avanzamos en paralelo
        tmpA = tmpA->next;
        tmpB = tmpB->next;
    }

    return nueva;
}
//============================0

/*
Tu tarea: Devolver una NUEVA lista que contenga todos los elementos de lista_A y todos los elementos de lista_B.
Regla de Oro: ¡Sin duplicados! Si un elemento está en A y en B, solo debe aparecer una vez en el resultado
. Si un elemento está repetido dentro de la misma lista A, también debe aparecer una sola vez.Regla de Platino: Las listas no vienen ordenadas.
Pista: Tu función auxiliar contiene (que ya sabes hacer perfecta) es tu mejor amiga aquí para mantener el código limpio.
*/
GList glist_union(GList lista_A, GList lista_B, FuncionComparadora cmp, FuncionCopia copy) {
    GList nueva = glist_crear();

    // 1. Recorremos la primera lista
    for (GNode *tmp = lista_A; tmp != NULL; tmp = tmp->next) {
        // Si el dato todavía NO está en nuestra lista de resultados, lo agregamos
        if (!contiene(nueva, tmp->data, cmp)) {
            nueva = insertar_al_final(nueva, tmp->data, copy);
        }
    }

    // 2. Recorremos la segunda lista (haciendo exactamente lo mismo)
    for (GNode *tmp = lista_B; tmp != NULL; tmp = tmp->next) {
        // Al chequear contra 'nueva', evitamos agregar cosas que ya trajimos de A, 
        // o que están repetidas dentro de B.
        if (!contiene(nueva, tmp->data, cmp)) {
            nueva = insertar_al_final(nueva, tmp->data, copy);
        }
    }

    return nueva;
}//============================0




//============================0
/*

Tienes una GList genérica donde sabes que todos los elementos son strings puros (char * creados con malloc).
 Necesitas censurar o actualizar una palabra específica.

Tu tarea: Implementar glist_reemplazar_palabra.

Recorres la lista buscando los nodos cuyo dato sea exactamente igual al string palabra_vieja.

Cuando lo encuentras, debes reemplazar ese dato por una copia física de palabra_nueva.

Regla de Oro: La lista es in-place (no creas nodos nuevos).

Regla de Platino: ¡El string viejo ocupaba memoria! Antes de asignarle el string nuevo al nodo, debes liberar la memoria del string viejo para no generar fugas de memoria.


(Pista: No hace falta usar funciones auxiliares raras aquí, un simple strcmp, free, malloc y strcpy adentro del bucle harán el trabajo).
*/
void glist_reemplazar_palabra(GList lista, char *palabra_vieja, char *palabra_nueva) {
    if (lista == NULL || palabra_vieja == NULL || palabra_nueva == NULL) return;

    for (GNode *tmp = lista; tmp != NULL; tmp = tmp->next) {
        // Casteamos el void* a char* para poder leer el string
        char *palabra_actual = (char *)tmp->data;

        if (strcmp(palabra_actual, palabra_vieja) == 0) {
            // 1. Liberamos la memoria del string viejo
            free(tmp->data);

            // 2. Pedimos nueva memoria para el string nuevo (+1 para el '\0')
            tmp->data = malloc(sizeof(char) * (strlen(palabra_nueva) + 1));

            // 3. Copiamos los caracteres a la nueva memoria
            strcpy((char *)tmp->data, palabra_nueva);
        }
    }
}


//===========================

/*
Tienes una GList de números enteros asignados dinámicamente (int *).
 Quieres separar esta lista en dos listas nuevas (lista_pares y lista_impares) cortando y 
 re-enganchando los nodos (Out-of-place pero reciclando los nodos originales, ¡sin malloc para nodos ni datos!).

La trampa: Si el número es múltiplo de 10 (10, 20, 30...), es considerado "corrupto". 
NO debe ir a ninguna de las dos listas. Debe ser completamente destruido (liberado el dato y liberado el nodo).

Regla de Oro: Recibes la lista original por referencia para desarmarla por completo. Al final, *lista_original debe ser NULL.

(Pista del compilador: Tienes 3 caminos posibles para cada nodo: va a pares, va a impares, o se va al free().
 ¡Cuidado con avanzar tu puntero temporal antes de destruir el nodo corrupto!)
*/
void glist_particion_destructiva(GList *lista_original, GList *lista_pares, GList *lista_impares) {
    // Escudo protector
    if (lista_original == NULL || *lista_original == NULL) {
        if (lista_pares) *lista_pares = NULL;
        if (lista_impares) *lista_impares = NULL;
        return;
    }

    GNode *tmp = *lista_original;
    *lista_original = NULL; // La original queda vacía inmediatamente

    *lista_pares = NULL;
    *lista_impares = NULL;
    GNode *cola_p = NULL;
    GNode *cola_i = NULL;

    while (tmp != NULL) {
        GNode *siguiente = tmp->next; // Guardamos el resto en el bolsillo
        tmp->next = NULL;             // Dejamos el nodo limpio

        int valor = *(int *)(tmp->data);

        if (valor % 10 == 0) {
            // CAMINO 1: Es corrupto. Destrucción total.
            free(tmp->data);
            free(tmp);
        } else if (valor % 2 == 0) {
            // CAMINO 2: Es par. Lo enganchamos en la lista de pares.
            if (*lista_pares == NULL) {
                *lista_pares = tmp;
            } else {
                cola_p->next = tmp;
            }
            cola_p = tmp;
        } else {
            // CAMINO 3: Es impar. Lo enganchamos en la lista de impares.
            if (*lista_impares == NULL) {
                *lista_impares = tmp;
            } else {
                cola_i->next = tmp;
            }
            cola_i = tmp;
        }

        tmp = siguiente; // Avanzamos al nodo que teníamos en el bolsillo
    }
}


//==========
/*
Tu tarea: Implementar glist_eliminar_k_desde_final_in_place. Debes eliminar (destruir dato y liberar nodo) el elemento que está en la posición k... empezando a contar desde atrás hacia adelante.Ejemplo: Si la lista es A -> B -> C -> D -> E y k = 2, debes eliminar la D.Regla de Oro: In-place absoluto. Se modifica la cabecera si es necesario (recibes GList *lista).Regla de Platino (La Trampa Mortal): ¡TIEMPO $O(N)$ ESTRICTO EN UNA SOLA PASADA! Prohibido calcular la longitud() primero. Prohibido recorrer la lista más de una vez. Todo se hace en un único bucle while
*/
void glist_eliminar_k_desde_final_in_place(GList *lista, int k, FuncionDestructora destroy) {
    // Escudo protector estándar + validación de K
    if (lista == NULL || *lista == NULL || k <= 0) return;

    GNode *explorador = *lista;
    GNode *ejecutor = *lista;

    // 1. Avanzamos el explorador 'k' pasos para crear la "distancia"
    for (int i = 0; i < k; i++) {
        if (explorador == NULL) return; // La lista tenía menos de 'k' elementos. No hacemos nada.
        explorador = explorador->next;
    }

    // 2. Caso especial crítico:
    // Si el explorador llegó a NULL exactamente al dar los 'k' pasos,
    // significa que la longitud de la lista es exactamente 'k'. 
    // Por lo tanto, el elemento a borrar ("el k-ésimo desde atrás") es el primero de todos.
    if (explorador == NULL) {
        GNode *a_borrar = *lista;
        *lista = (*lista)->next; // Movemos la cabecera
        destroy(a_borrar->data);
        free(a_borrar);
        return;
    }

    // 3. Movemos ambos punteros a la misma velocidad.
    // Frenamos cuando el explorador sea el ÚLTIMO NODO (su next es NULL).
    // Esto hace que 'ejecutor' quede parado UN NODO ANTES del nodo que queremos borrar.
    while (explorador->next != NULL) {
        explorador = explorador->next;
        ejecutor = ejecutor->next;
    }

    // 4. El ejecutor está parado justo atrás del nodo condenado. Lo puenteamos.
    GNode *a_borrar = ejecutor->next;
    ejecutor->next = a_borrar->next; // El puente salva el resto de la lista

    // 5. Destrucción final
    destroy(a_borrar->data);
    free(a_borrar);
}


//==========

typedef struct {
    char *ip_cliente;
    int status_code; // ej: 200, 404, 500
} PeticionLog;


void *peticion_copia_profunda(void *dato) {
    PeticionLog *p = (PeticionLog *)dato;
    PeticionLog *copia = malloc(sizeof(PeticionLog));
    
    copia->status_code = p->status_code;
    copia->ip_cliente = malloc(sizeof(char) * (strlen(p->ip_cliente) + 1));
    strcpy(copia->ip_cliente, p->ip_cliente);
    
    return copia;
}

// Función auxiliar que pide la materia para que las HOF no lloren
void *no_copiar(void *dato) {
    return dato;
}

/*
Tu tarea: Implementar glist_agrupar_por_ip. Recibes una lista plana de PeticionLog. Debes devolver una NUEVA lista de listas (GList donde cada data es otra GList).

Cada sub-lista debe contener copias físicas de las peticiones que provengan de la misma IP.

Regla de Oro: Out-of-place. La lista original no se toca.

El desafío algorítmico: A medida que recorres la lista original, para cada nodo, tienes que buscar en tu nueva estructura si ya existe una sub-lista para esa IP. Si existe, lo agregas a esa sub-lista. Si no existe, creas una sub-lista nueva, metes el dato ahí, y agregas esa sub-lista a la lista principal.
*/
GList glist_agrupar_por_ip(GList original) {
    GList principal = glist_crear(); 

    for (GNode *tmp_orig = original; tmp_orig != NULL; tmp_orig = tmp_orig->next) {
        PeticionLog *log_actual = (PeticionLog *)tmp_orig->data;
        
        int sublista_encontrada = 0;
        GNode *tmp_prin = principal;

        // El bucle corta naturalmente si llegamos al final O si encontramos la IP
        while (tmp_prin != NULL && sublista_encontrada == 0) {
            GList sublista = (GList)tmp_prin->data; 
            PeticionLog *primer_log = (PeticionLog *)sublista->data;

            if (strcmp(primer_log->ip_cliente, log_actual->ip_cliente) == 0) {
                // ¡ENCONTRAMOS LA IP! 
                tmp_prin->data = agregar_al_inicio(sublista, log_actual, peticion_copia_profunda);
                
                // Levantamos la bandera. Esto hará que el while termine en la próxima evaluación.
                sublista_encontrada = 1; 
            }
            
            // Avanzamos el puntero (no importa si lo encontramos o no, 
            // porque si lo encontramos, el while cortará de todos modos)
            tmp_prin = tmp_prin->next;
        }

        // Si el while terminó y la bandera sigue baja, creamos el grupo nuevo
        if (sublista_encontrada == 0) {
            GList nueva_sublista = glist_crear();
            nueva_sublista = agregar_al_inicio(nueva_sublista, log_actual, peticion_copia_profunda);
            principal = agregar_al_inicio(principal, nueva_sublista, no_copiar);
        }
    }
    
    return principal;
}
//============================0


typedef struct {
    char *username;
    char **direcciones_ip; // Un arreglo dinámico de strings (char *)
    int cant_ips;
} Usuario;

/*
Tu tarea:
Implementar usuario_copia:
 Debe hacer un malloc para el usuario, un malloc para el string username, 
 un malloc para el arreglo de punteros direcciones_ip, y un malloc por cada string IP adentro de ese arreglo.

Implementar usuario_destruir: 
La función inversa. Si liberas el Usuario antes de liberar sus IPs, pierdes la memoria para siempre (Memory Leak). 
Debes liberar de "adentro hacia afuera".

*/
void *usuario_copia(void *dato) {
    Usuario *u = (Usuario *)dato;
    
    // 1. Malloc para la cáscara externa (la estructura principal)
    Usuario *copia = malloc(sizeof(Usuario));

    // Copiamos el dato estático
    copia->cant_ips = u->cant_ips;

    // 2. Malloc y copia para el string simple
    copia->username = malloc(sizeof(char) * (strlen(u->username) + 1));
    strcpy(copia->username, u->username);

    // 3. EL ARREGLO DINÁMICO: 
    // Primero, malloc para crear el "estante" que guardará los punteros a los strings.
    // Ojo al tipo: sizeof(char *)
    copia->direcciones_ip = malloc(sizeof(char *) * u->cant_ips);

    // 4. Recorremos el estante haciendo malloc para cada string individual
    for (int i = 0; i < u->cant_ips; i++) {
        copia->direcciones_ip[i] = malloc(sizeof(char) * (strlen(u->direcciones_ip[i]) + 1));
        strcpy(copia->direcciones_ip[i], u->direcciones_ip[i]);
    }

    return copia;
}



void usuario_destruir(void *dato) {
    if (dato == NULL) return;
    Usuario *u = (Usuario *)dato;

    // Liberamos de adentro hacia afuera para no perder referencias

    // 1. Liberamos cada string individual del arreglo
    for (int i = 0; i < u->cant_ips; i++) {
        free(u->direcciones_ip[i]);
    }
    
    // 2. Liberamos el "estante" que contenía los punteros
    free(u->direcciones_ip);

    // 3. Liberamos el string simple
    free(u->username);

    // 4. Liberamos la cáscara principal
    free(u);
}
