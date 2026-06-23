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

    GNode * inicio=lista;
    while(inicio!=NULL){
        GNode *recorrido = inicio;
        while(recorrido->next != NULL){
            if(comp(recorrido->next->data, inicio->data) == 0){
                GNode *tmp = recorrido->next;
                recorrido->next = tmp->next; 
                destroy(tmp->data);
                free(tmp);
            } else {
                recorrido = recorrido->next;
            }
        }
        inicio = inicio->next;
    }
}


void glist_eliminar_duplicados_consecutivos(GList lista, FuncionComparadora comp, FuncionDestructora destroy){
    if(lista==NULL) return;

    GNode * inicio=lista;

    while(inicio!=NULL && inicio->next!=NULL){
        if(comp(inicio->data,inicio->next->data)==0){
            inicio->next = glist_eliminar_elemento(inicio->next, inicio->data, comp, destroy);
        }else inicio=inicio->next;
    }
}

void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

void glist_reverso_in_place(GList *lista) {
    if (lista == NULL || *lista == NULL) return;

    GNode *inicio = *lista;
    GNode *prev = NULL;
    GNode *siguiente = NULL;

    while (inicio != NULL) {
        siguiente = inicio->next; 
        inicio->next = prev;
        
        prev = inicio;            
        inicio = siguiente;       
    }

    *lista = prev; 
}


GList glist_copiar_recursivo(GList lista, FuncionCopia copy) {
    if (lista == NULL) return NULL; 
    
    GNode *nuevo = malloc(sizeof(GNode));
    
    nuevo->data = copy(lista->data);
    
    nuevo->next = glist_copiar_recursivo(lista->next, copy);

    return nuevo;
}


GList glist_map_in_place(GList lista, FUncionTransformadora f, FuncionDestructora destroy){
    for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
        void * elemento=f(tmp->data);
        destroy(tmp->data);
        tmp->data=elemento;
    }
    return lista;
}

GList glist_filtrarV2_destruir_si(GList lista, Predicado p, FuncionDestructora destroy) {
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

    GNode *node = *lista;
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


    GNode * inicio=*lista_original;
    GNode * la=NULL;
    GNode * lb=NULL;

    int indice=0;

    while(inicio!=NULL){
        GNode *siguiente = inicio->next;
        inicio->next=NULL;

        if(indice%2==0){
            if(*lista_A==NULL) *lista_A=inicio;
            else la->next=inicio;
            la=inicio;
        }else{
            if(*lista_B==NULL) *lista_B=inicio;
            else lb->next=inicio;
            lb=inicio;
        }
        inicio=siguiente;
        indice++;
    }

    *lista_original=NULL;
}



GList glist_racha_mas_larga(GList lista, Predicado p, FuncionCopia copy) {
    if (lista == NULL) return NULL;

    int max_len = 0;
    GNode *mejor_inicio = NULL;

    int actual_len = 0;
    GNode *actual_inicio = NULL;

    // --- PRIMERA PASADA: Búsqueda del campeón ---
    for (GNode *tmp = lista; tmp != NULL; tmp = tmp->next) {
        if (p(tmp->data)) { 
            if (actual_len == 0) actual_inicio = tmp; 
            
            actual_len++;
            

            if (actual_len > max_len) {
                max_len = actual_len;
                mejor_inicio = actual_inicio;
            }
        } else { 
            actual_len = 0;
            actual_inicio = NULL;
        }
    }

    // --- SEGUNDA PASADA: Construcción ---
    GList nueva = glist_crear();

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
  for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
    if(comp(tmp->data,dato_buscado)==0) return 1;
  }
  return 0;
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
            GNode *tmp = node;
            node = node->next;
            if (prev == NULL) lista = node; 
            else prev->next = node;
            
            destroy(tmp->data);
            free(tmp); 
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
            GNode *tmp = node;
            node = node->next;
            if (prev == NULL) lista = node; 
            else prev->next = node;
            
            destroy(tmp->data);
            free(tmp); 
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


void glist_intercalar_in_place(GList *lista1, GList *lista2){
    if(lista1 == NULL || lista2 == NULL || *lista2 == NULL || *lista1 == NULL) return;

    // if(*l1  == NULL) {
    //     *l1  = *l2;
    //     *l2 = NULL;
    //     return;
    // }

    GNode * l1 = *lista1 ;
    GNode * l2 = *lista2;

    while (l1 != NULL && l2 != NULL) {
        
        GNode * sig_l1 = l1->next;
        GNode * sig_l2 = l2->next;

        // Primer cruce: l1 -> l2
        l1->next = l2;
        
        //  Segundo cruce: l2 -> l1 
        if (sig_l1 != NULL) {
            l2->next = sig_l1;
        }

        l1 = sig_l1;
        l2 = sig_l2;
    }

    *lista2 = NULL;
}


void glist_mover_al_frente(GList *lista, void *dato_buscado, FuncionComparadora comp){
    if(lista==NULL||*lista==NULL) return;

    GNode * inicio = *lista;
    GNode * prev=NULL;

    while(inicio!=NULL){
        if(comp(inicio->data,dato_buscado)==0){
            if(prev==NULL)  inicio = inicio->next; //ya esta en primer lugar.
            else{
                prev->next=inicio->next;

                inicio->next = *lista;
                *lista=inicio;

                inicio=prev->next;
            }
        }
        else{
            prev = inicio;
            inicio=inicio->next;
        }
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

    if (*lista == NULL || (*lista)->next == NULL) return;

    GList mitad_izq = *lista;
    GList mitad_der = glist_partir(*lista);

    merge_sort(&mitad_izq,comp);
    merge_sort(&mitad_der,comp);

    *lista = concatenar_ordenado(mitad_izq, mitad_der,comp);
}

//!SECTION




