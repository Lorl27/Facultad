#include "glist.h"
#include <stdlib.h>

//SECTION -  COMUNES

GList glist_crear() {
     return NULL; 
}


void glist_destruir(GList list, FuncionDestructora destroy) {
  if(list==NULL) return;

    GNode * nodo=list;
    GNode * tmp;
    while (nodo != NULL) {
        tmp=nodo;
        nodo = nodo->next;
        destroy(tmp->data);
        free(tmp);
    }
}

int glist_vacia(GList list) {
    return list == NULL;
}

int longitud(GList lista){
  int contador=0;
  GNode *tmp=lista;
  while(tmp!=NULL){
    contador++;
    tmp=tmp->next;
  }
  return contador;
}


//eliminar k desde el final == long-k
GList eliminar(GList lista, FuncionDestructora destroy, int pos){
 if(pos<0 || pos>=longitud(lista) || !lista ) return lista;


  if(pos==0){
    GNode * tmp= lista;
    lista=lista->next;
    destroy(tmp->data);
    free(tmp);
    return lista;
  }

  GNode * inicio= lista;
  GNode * actual= lista->next;
  int contador=1;

  while(actual!=NULL && contador<pos){
    inicio=actual;
    actual=actual->next;
    contador++;
  }

  if(actual!=NULL && contador==pos){
    inicio->next=actual->next;
    destroy(actual->data);
    free(actual);
  }


  return lista;
}


void glist_eliminar_duplicados(GList lista, FuncionComparadora comp, FuncionDestructora destroy){
    if(lista==NULL) return;

    GNode * actual=lista;
    while(actual!=NULL){
        GNode *recorrido = actual;
        while(recorrido->next != NULL){
            if(comp(recorrido->next->data, actual->data) == 0){
                GNode *clon = recorrido->next;
                recorrido->next = clon->next; // Puenteamos el clon
                destroy(clon->data);
                free(clon);
            } else {
                recorrido = recorrido->next;
            }
        }
        actual = actual->next;
    }
}


void glist_eliminar_duplicados_consecutivos(GList lista, FuncionComparadora comp, FuncionDestructora destroy){
    if(lista==NULL) return;

    GNode * actual=lista;

    while(actual!=NULL && actual->next!=NULL){
        if(comp(actual->data,actual->next->data)==0){
            actual->next = glist_eliminar_elemento(actual->next, actual->data, comp, destroy);
        }else actual=actual->next;
    }
}

void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

void glist_reverso_in_place(GList *lista) {
    if (lista == NULL || *lista == NULL) return;

    GNode *prev = NULL;
    GNode *actual = *lista;
    GNode *siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->next; 
        
        prev = actual;            
        actual = siguiente;       
    }

    *lista = prev; 
}


GList glist_copiar_recursivo(GList lista, FuncionCopia copy) {
    // Caso base: si la lista original está vacía, la copia es vacía.
    if (lista == NULL) {
        return NULL; 
    }

    // 1. Pedimos memoria para el nodo clon
    GNode *nuevo = malloc(sizeof(GNode));
    
    // 2. Copiamos el dato usando tu función
    nuevo->data = copy(lista->data);
    
    // 3. La magia recursiva: el "next" engancha con la copia del resto
    nuevo->next = glist_copiar_recursivo(lista->next, copy);

    return nuevo;
}


void glist_map_in_place(GList lista, FUncionTransformadora f, FuncionDestructora destroy){
    for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
        void * elemento=f(tmp->data);
        destroy(tmp->data);
        tmp->data=elemento;
    }
    return lista;
}

GList glist_filtrarV2_destruir_si(GList lista, Predicado p) {
    if (!lista) return NULL;

    GNode *node = lista;
    GNode *prev = NULL;

    while (node != NULL) {
        if (p(node->data)) {
            // mantener nodo
            prev = node;
            node = node->next;   
        } else {
            //lo eliminamos
            GNode *tmp = node;
            node = node->next;

            if (prev == NULL) lista = node;
            else prev->next = node;
            
            destroy(tmp->data);
            free(tmp);  
           
        }
    }

    return lista;
}

GList glist_filtrarV3(GList *lista, Predicado p){
    if(lista==NULL || * lista==NULL) return NULL;

     GNode *node = lista;
    GNode *prev = NULL;

    GNode * nueva=NULL;
    GNode *cola_falsos = NULL;

     while (node != NULL) {
        if (p(node->data)) {
            // mantener nodo
            prev = node;
            node = node->next;   
        }else{
            //lo eliminamos
           GNode *tmp = node;
            node = node->next;

            if(prev==NULL) *lista = node;
            else prev->next=node;
            
            tmp->next = NULL;
            if(nueva==NULL) nueva=tmp;
            else cola_falsos->next=tmp;
            
            cola_falsos=tmp;

           
        }
    }

    return nueva;

}


GList glist_partir(GList lista) {
    if (lista == NULL) return NULL;
    
    int len = longitud(lista);
    if (len == 1) return NULL;

    int mitad = (len % 2 == 0) ? (len / 2) : (len / 2) + 1;
    
    GNode *tmp = lista;
    int contador = 1;

    while (tmp != NULL && contador < mitad) {
        tmp = tmp->next;
        contador++;
    }

    GList segunda_mitad = tmp->next;
    
    tmp->next = NULL;

    return segunda_mitad;
}


void glist_repartir_alternado(GList *lista_original, GList *lista_A, GList *lista_B){
    if(lista_original==NULL || * lista_original==NULL)return;


    GNode * la=NULL;
    GNode * lb=NULL;
    GNode * cabecera=*lista_original;

    int indice=0;

    while(cabecera!=NULL){
        GNode *siguiente = cabecera->next;
        cabecera->next=NULL;

        if(indice%2==0){
            if(*lista_A==NULL) *lista_A=cabecera;
            else la->next=cabecera;
            la=cabecera;
        }else{
            if(*lista_B==NULL) *lista_B=cabecera;
            else lb->next=cabecera;
            lb=cabecera;
        }
        cabecera=siguiente;
        indice++;
    }

    *lista_original=NULL;
}



GList glist_racha_mas_larga(GList original, Predicado p, FuncionCopia copy) {
    if (original == NULL) return NULL;

    // Variables para el campeón actual
    int max_len = 0;
    GNode *mejor_inicio = NULL;

    // Variables para el retador (la racha que estamos contando)
    int actual_len = 0;
    GNode *actual_inicio = NULL;

    // --- PRIMERA PASADA: Búsqueda del campeón ---
    for (GNode *tmp = original; tmp != NULL; tmp = tmp->next) {
        if (p(tmp->data)) { // Cumple la condición
            // Si es el primer elemento de esta racha, marcamos el inicio
            if (actual_len == 0) actual_inicio = tmp; 
            
            actual_len++;
            
            // ¿Superamos el récord?
            if (actual_len > max_len) {
                max_len = actual_len;
                mejor_inicio = actual_inicio;
            }
        } else { // Rompió la racha
            actual_len = 0;
            actual_inicio = NULL;
        }
    }

    // --- SEGUNDA PASADA: Construcción ---
    GList nueva = glist_crear();
    
    // Si max_len es 0, significa que ningún elemento cumplió el predicado
    if (max_len == 0) return nueva; 

    // Copiamos físicamente la cantidad exacta de nodos desde el nodo ganador
    GNode *tmp = mejor_inicio;
    for (int i = 0; i < max_len; i++) {
        nueva = insertar_al_final(nueva, tmp->data, copy);
        tmp = tmp->next;
    }

    return nueva;
}

void **glist_a_array(GList lista, int *out_len, FuncionCopia copy) {
    int len = longitud(lista);
    *out_len = len; 
    
    if (len == 0) return NULL;

    void **array = malloc(sizeof(void *) * len);
    
    int i = 0;
    for (GNode *tmp = lista; tmp != NULL; tmp = tmp->next) {
        array[i] = copy(tmp->data); 
        i++;
    }

    return array;
}

//!SECTION 

//SECTION - SIMILARES 


GList insertar(GList lista, void * dato, FuncionCopia copy,int pos){
  if(pos<0 || pos>longitud(lista) ) return lista;

  GNode * nuevo=malloc(sizeof(GNode));
  nuevo->data=copy(dato);

  if(pos==0){
    nuevo->next=lista;
    return nuevo;
  }

  if(!lista) return lista;

  GNode * inicio= lista;
  GNode * actual= lista->next;
  int contador=1;

  while(inicio!=NULL && contador<pos){
    inicio=actual;
    actual=actual->next;
    contador++;
  }

  if(inicio!=NULL && contador==pos){
    nuevo->next=actual;
    inicio->next=nuevo;
  }


  return lista;
}

SGList insertar_ordenado(SGList lista, void * dato, FuncionCopia copy, FuncionComparadora comp){
    GNode *nuevo = malloc(sizeof(GNode));
    nuevo->data = copy(dato);

    if (lista == NULL || comp(lista->data, dato) > 0) {
        nuevo->next = lista;
        return nuevo; 
    }

    GNode *inicio = lista;
    GNode *actual = lista->next;

    while (actual != NULL && comp(actual->data, dato) <= 0) {
        inicio = actual;
        actual = actual->next;
    }

    nuevo->next = actual;
    inicio->next = nuevo;

    return lista;
}

int contiene(GList lista, void * dato_buscado , FuncionComparadora comp){
  int x=0;
  for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
    if(comp(tmp->data,dato_buscado)==0) return x;
    x++;
  }
  return -1;
}

int contiene_ordenado(GList lista, void *dato, FuncionComparadora comp) {
    for (GNode *tmp = lista; tmp != NULL; tmp = tmp->next) {
        int comparacion = comp(tmp->data, dato);
        
        if (comparacion == 0) {
            return 1; 
        }
        
        if (comparacion > 0) {
            return 0; // Cortamos la búsqueda temprano
        }
    }
    return 0; 
}

GList glist_eliminar_elemento(GList lista, void *dato, FuncionComparadora comp, FuncionDestructora destroy) {
    if (lista == NULL) return NULL;

    GNode *node = lista;
    GNode *prev = NULL;

    while (node != NULL) {
      int cmp = comp(node->data, dato);
        if (cmp == 0) {
            if (prev == NULL) lista = node->next; 
            else prev->next = node->next;
            
            destroy(node->data);
            free(node);
            return lista;
        }

        prev = node;
        node = node->next;
    }

    return lista; 
}


SGList eliminar_elemento_ordenado(SGList lista, void *dato, FuncionComparadora comp, FuncionDestructora destroy) {
    if (lista == NULL) return NULL;

    GNode *node = lista;
    GNode *prev = NULL;

    while (node != NULL) {
        int cmp = comp(node->data, dato);

        if (cmp == 0) {
            if (prev == NULL) lista = node->next;
            else prev->next = node->next;
            
            destroy(node->data);
            free(node);
            return lista;
        } 
        // ya pasamos el lugar donde debería estar
        else if (cmp > 0) return lista;
        
        prev = node;
        node = node->next;
    }

    return lista;
}


GList glist_intersercar(GList lista1, GList lista2, FuncionComparadora comp, FuncionCopia copy) {
    GList lista_resultado = glist_crear();

    for (GNode *tmp1 = lista1; tmp1 != NULL; tmp1 = tmp1->next) {
        if (contiene(lista2, tmp1->data, comp)) {
           // Evitamos duplicados
            if (!contiene(lista_resultado, tmp1->data, comp)) {
                lista_resultado = insertar_final(lista_resultado, tmp1->data, copy);
            }
        }
    }

    return lista_resultado;
}


SGList sglist_intersecar_ordenado(SGList lista1, SGList lista2, FuncionComparadora comp, FuncionCopia copy) {
    SGList resultado = glist_crear();
    
    GNode *tmp1 = lista1;
    GNode *tmp2 = lista2;

    while (tmp1 != NULL && tmp2 != NULL) {
        int comparacion = comp(tmp1->data, tmp2->data);

        if (comparacion == 0) {
            resultado = insertar_final(resultado, tmp1->data, copy);
            
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
            
        } 
        else if (comparacion < 0)  tmp1 = tmp1->next; 
        else tmp2 = tmp2->next;
        
    }

    
    return resultado;
}


GList glist_concatenar(GList lista1, GList lista2) {
    if (lista1 == NULL) return lista2;

    GNode *tmp = lista1;
    
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = lista2;

    return lista1;
}


GList concatenar_ordenado(GList l1, GList l2, FuncionComparadora comp) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    GList resultado = NULL;

    if (comp(l1->data, l2->data) <= 0) {
        resultado = l1;
        resultado->next = concatenar_ordenado(l1->next, l2, comp);
    } else {
        resultado = l2;
        resultado->next = concatenar_ordenado(l1, l2->next, comp);
    }
    return resultado;
}


GList array_a_glist(void **array, int len, FuncionCopia copy) {
    GList lista = glist_crear();
    
    for (int i = len - 1; i >= 0; i--) {
        lista = insertar_inicio(lista, array[i], copy);
    }
    
    return lista;
}


GList array_a_sglist(void **array, int long_array, FuncionCopia copy, FuncionComparadora comp) {
    SGList lista = sglist_crear();
    
    for (int i = 0; i < long_array; i++) {
        lista = sglist_insertar(lista, array[i], copy, comp);
    }
    
    return lista;
}

//!SECTION

//SECTION -  EXCLUYENTES

SGList sglist_intercalar_ordenado(SGList lista1, SGList lista2, FuncionCopia copy, FuncionComparadora comp) {
    SGList resultado = glist_crear();

    SGList clon1 = glist_copiar_recursivo(lista1, copy);
    SGList clon2 = glist_copiar_recursivo(lista2, copy);

    return concatenar_ordenado(clon1, clon2, comp);
}


void glist_intercalar_in_place(GList *lista_base, GList *lista_extra){
    if(lista_base == NULL || lista_extra == NULL || *lista_extra == NULL) return;

    if(*lista_base == NULL) {
        *lista_base = *lista_extra;
        *lista_extra = NULL;
        return;
    }

    GNode * p_base = *lista_base;
    GNode * p_extra = *lista_extra;

    while (p_base != NULL && p_extra != NULL) {
        
        GNode * sig_base = p_base->next;
        GNode * sig_extra = p_extra->next;

        // 2. Primer cruce: Base -> Extra
        p_base->next = p_extra;
        
        // 3. Segundo cruce: Extra -> Base 
        if (sig_base != NULL) {
            p_extra->next = sig_base;
        }

        p_base = sig_base;
        p_extra = sig_extra;
    }

    *lista_extra = NULL;
}


void glist_mover_al_frente(GList *lista, void *dato_buscado, FuncionComparadora comp){
    if(lista==NULL||*lista==NULL) return;
    GNode * prev=NULL;
    GNode * actual = *lista;

    while(actual!=NULL){
        if(comp(actual->data,dato_buscado)==0){
            if(prev==NULL) return; //ya esta en primer lugar.
            else{
                prev->next=actual->next;
                actual->next = *lista;
                *lista=actual;
            }
        }
        prev = actual;
        actual=actual->next;
    }
}


void glist_rotar_derecha_k_pos(GList *lista, int k) {
    if (lista == NULL || *lista == NULL || (*lista)->next == NULL || k <= 0) return;

    int n = 1;
    GNode *ultimo = *lista;
    while (ultimo->next != NULL) {
        n++;
        ultimo = ultimo->next;
    }

    // Si k es múltiplo de n (ej: rotar 5 veces una lista de 5), la lista queda igual
    k = k % n;
    if (k == 0) return;

    // 2. MAGIA: Conectamos el final con el principio. ¡Tenemos un círculo!
    ultimo->next = *lista;

    // 3. Buscamos la nueva cola (que estará en la posición N - k)
    int pasos_nueva_cola = n - k;
    GNode *nueva_cola = *lista;
    
    // Caminamos hasta el nodo que será el último
    for (int i = 1; i < pasos_nueva_cola; i++) {
        nueva_cola = nueva_cola->next;
    }

    // 4. Rompemos el círculo
    *lista = nueva_cola->next; // La nueva cabeza es el que le sigue a la nueva cola
    nueva_cola->next = NULL;   // Sellamos la lista para que vuelva a ser lineal
}

void merge_sort(GList *lista, FuncionComparadora comp) {
    GList cabeza = *lista;

    // Caso base: si la lista está vacía o tiene 1 solo elemento, ya está ordenada.
    if (cabeza == NULL || cabeza->next == NULL) {
        return;
    }

    // 1. DIVIDIR
    GList mitad_izq = cabeza;
    GList mitad_der = slist_partir(cabeza); // Corta 'cabeza' a la mitad y retorna el inicio de la segunda

    // 2. ORDENAR RECURSIVAMENTE
    merge_sort(&mitad_izq,comp);
    merge_sort(&mitad_der,comp);

    // 3. VENCER (Combinar)
    // Guardamos el resultado de la combinación como la nueva cabeza de la lista
    *lista = concatenar_ordenado(mitad_izq, mitad_der,comp);
}

//!SECTION




