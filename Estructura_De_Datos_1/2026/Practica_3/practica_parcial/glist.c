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



void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

typedef int (*FuncionVisitanteCorte)(void *dato);

void sglist_recorrer_con_corte(SGList lista, FuncionVisitanteCorte visit) {
    GNode *tmp = lista;
    int seguir = 1;

    while (tmp != NULL && seguir) {
        seguir = visit(tmp->data);  // visitante decide si continuar
        tmp = tmp->next;
    }
}


GList glist_filtrarV2(GList lista, FuncionCopia c, Predicado p) {
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



GList glist_reverso(GList lista, FuncionCopia copy){
  if(!lista) return lista;

  GList reverso = glist_crear();
  GNode * tmp = lista;

  while(tmp!=NULL){
    reverso=glist_agregar_inicio(reverso,tmp->data,copy);
    tmp=tmp->next;
  }
  return reverso;

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


GList glist_partir(GList lista) {
    if (lista == NULL) return NULL;
    
    int len = longitud(lista);
    if (len == 1) return NULL;

    // Cálculo matemático para asegurar que si es impar, la primera mitad se quede con el extra
    int mitad = (len % 2 == 0) ? (len / 2) : (len / 2) + 1;
    
    GNode *tmp = lista;
    int contador = 1;

    // Avanzamos hasta el nodo que será el ÚLTIMO de la primera mitad
    while (tmp != NULL && contador < mitad) {
        tmp = tmp->next;
        contador++;
    }

    // Guardamos la cabeza de la segunda mitad
    GList segunda_mitad = tmp->next;
    
    // ¡CORTAMOS LA LISTA! (Este es el paso fundamental in-place)
    tmp->next = NULL;

    return segunda_mitad;
}

/* * De GList (o SGList) a Array.
 * Devuelve un void**, y guarda la longitud en el puntero out_len.
 */
void **glist_a_array(GList lista, int *out_len, FuncionCopia copy) {
    int len = longitud(lista);
    *out_len = len; // Guardamos el tamaño para saber cuánto recorrer luego
    
    if (len == 0) return NULL;

    // Pedimos memoria para el array de punteros
    void **array = malloc(sizeof(void *) * len);
    
    int i = 0;
    for (GNode *tmp = lista; tmp != NULL; tmp = tmp->next) {
        array[i] = copy(tmp->data); // Llenamos el array copiando los datos
        i++;
    }

    return array;
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

//!SECTION 

//SECTION - SIMILARES 

GList glist_filtrar(GList lista, FuncionCopia c, Predicado p){
  GList nueva = glist_crear();
  for(GNode *node = lista; node != NULL; node = node->next){
    if(p(node->data)){
      nueva=glist_agregar_inicio(nueva,node->data,c);
    }
  }
  return nueva;
}

GList glist_filtrar(GList lista, FuncionCopia c, Predicado p,FuncionComparadora comp){
  GList nueva = glist_crear();
  for(GNode *node = lista; node != NULL; node = node->next){
    if(p(node->data)){
      nueva=sglist_insertar(nueva,node->data,c,comp);
    }
  }
  return nueva;
}



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

SGList sglist_insertar(SGList lista, void * dato, FuncionCopia copy, FuncionComparadora comp){
    GNode *nuevo = malloc(sizeof(GNode));
    nuevo->data = copy(dato);

    //Caso Base: Lista vacía o el nuevo es MENOR que la cabeza actual
    // comp() retorna > 0 si lista->data es mayor que dato
    if (lista == NULL || comp(lista->data, dato) > 0) {
        nuevo->next = lista;
        return nuevo; // Nueva cabeza
    }

    GNode *inicio = lista;
    GNode *actual = lista->next;

    // Caminamos MIENTRAS el 'actual' sea MENOR o IGUAL al 'dato'
    while (actual != NULL && comp(actual->data, dato) <= 0) {
        inicio = actual;
        actual = actual->next;
    }

    nuevo->next = actual;
    inicio->next = nuevo;

    return lista;
}

GList eliminar(GList lista, FuncionDestructora destroy, int pos){
 if(pos<0 || pos>=longitud(lista) ) return lista;


  if(pos==0){
    GNode * tmp= lista;
    lista=lista->next;
    destroy(tmp->data);
    free(tmp);
    return lista;
  }

  if(!lista) return lista;

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

SGList sglist_eliminar(SGList lista, void *dato, FuncionComparadora comp, FuncionDestructora destroy) {
    if (lista == NULL) return NULL;

    GNode *curr = lista;
    GNode *prev = NULL;

    while (curr != NULL) {
        int cmp = comp(curr->data, dato);

        if (cmp == 0) {
            // encontrado → eliminar
            if (prev == NULL) {
                lista = curr->next;
            } else {
                prev->next = curr->next;
            }
            destroy(curr->data);
            free(curr);
            return lista;
        } else if (cmp > 0) {
            // ya pasamos el lugar donde debería estar
            return lista;
        }

        prev = curr;
        curr = curr->next;
    }

    return lista;
}


int buscar(GList lista, void * dato_buscado , FuncionComparadora comp){
  int x=0;
  for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
    if(comp(tmp->data,dato_buscado)==0) return x;
    x++;
  }
  return -1;
}

int sglist_buscar(GList lista, void *dato, FuncionComparadora comp) {
    for (GNode *tmp = lista; tmp != NULL; tmp = tmp->next) {
        int comparacion = comp(tmp->data, dato);
        
        if (comparacion == 0) {
            return 1; 
        }
        
        if (comparacion > 0) {
            // El dato actual de la lista es MAYOR al que buscamos.
            // Como la lista está ordenada, es imposible que esté más adelante.
            return 0; // Cortamos la búsqueda temprano
        }
    }
    return 0; 
}



GList map(GList lista, FUncionTransformadora fun, FuncionCopia copy){
  if(!lista) return lista;
  GList listaNueva= glist_crear();
  for(GNode * tmp=lista;tmp!=NULL;tmp=tmp->next){
    listaNueva=insertar_inicio(listaNueva,fun(tmp->data),copy);
  }

  listaNueva=glist_reverso(listaNueva,copy);
  return listaNueva;
}

SGList sglist_map(SGList lista, FUncionTransformadora fun, FuncionCopia copy, FuncionComparadora comp) {
    if (!lista) return NULL;
    
    SGList listaNueva = glist_crear();
    
    for (GNode *tmp = lista; tmp != NULL; tmp = tmp->next) {
        void *dato_transformado = fun(tmp->data);
        
        // La magia está acá: usamos sglist_insertar para que el nuevo dato 
        // caiga exactamente en la posición que le corresponde.
        listaNueva = sglist_insertar(listaNueva, dato_transformado, copy, comp);
        
        // Nota: dependiendo de cómo manejes la memoria en 'fun', 
        // quizás necesites liberar 'dato_transformado' después de copiarlo.
    }

    return listaNueva;
}

/* * De Array a GList (Común).
 * Mantiene el mismo orden que traía el array.
 */
GList array_a_glist(void **array, int len, FuncionCopia copy) {
    GList lista = glist_crear();
    
    // Lo más eficiente es recorrer al revés e insertar al inicio
    // (insertar_final tiene que recorrer toda la lista cada vez y es más lento)
    for (int i = len - 1; i >= 0; i--) {
        lista = insertar_inicio(lista, array[i], copy);
    }
    
    return lista;
}


//de array a sglist
GList sglist_arr(void **array, int long_array, FuncionCopia copy, FuncionComparadora comp) {
    SGList lista = sglist_crear(); // Empezamos con lista vacía
    
    for (int i = 0; i < long_array; i++) {
        // Vamos insertando cada elemento. ¡La función se encarga de ordenarlos!
        lista = sglist_insertar(lista, array[i], copy, comp);
    }
    
    return lista;
}

GList glist_intercalar(GList lista1, GList lista2, FuncionCopia copy) {
    GList lista_resultado = glist_crear();
    
    GNode *tmp1 = lista1;
    GNode *tmp2 = lista2;

    // Mientras quede algo en ALGUNA de las dos listas
    while (tmp1 != NULL || tmp2 != NULL) {
        
        if (tmp1 != NULL) {
            lista_resultado = insertar_final(lista_resultado, tmp1->data, copy);
            tmp1 = tmp1->next;
        }
        
        if (tmp2 != NULL) {
            lista_resultado = insertar_final(lista_resultado, tmp2->data, copy);
            tmp2 = tmp2->next;
        }
    }

    return lista_resultado;
}

SGList sglist_intercalar_ordenado(SGList lista1, SGList lista2, FuncionCopia copy, FuncionComparadora comp) {
    SGList resultado = glist_crear();
    GNode *tmp1 = lista1;
    GNode *tmp2 = lista2;

    // Recorremos ambas y vamos insertando el menor de los dos
    while (tmp1 != NULL && tmp2 != NULL) {
        if (comp(tmp1->data, tmp2->data) <= 0) {
            resultado = insertar_final(resultado, tmp1->data, copy);
            tmp1 = tmp1->next;
        } else {
            resultado = insertar_final(resultado, tmp2->data, copy);
            tmp2 = tmp2->next;
        }
    }

    // Si sobraron elementos en lista1, los agregamos al final
    while (tmp1 != NULL) {
        resultado = insertar_final(resultado, tmp1->data, copy);
        tmp1 = tmp1->next;
    }
    // Si sobraron en lista2, lo mismo
    while (tmp2 != NULL) {
        resultado = insertar_final(resultado, tmp2->data, copy);
        tmp2 = tmp2->next;
    }

    return resultado;
}


GList glist_intersercar_custom(GList lista1, GList lista2, FuncionComparadora comp, FuncionCopia copy) {
    GList lista_resultado = glist_crear();

    // Recorremos todos los elementos de la primera lista
    for (GNode *tmp1 = lista1; tmp1 != NULL; tmp1 = tmp1->next) {
        
        // Verificamos si ese elemento EXISTE en la lista 2 (usando tu funcion)
        if (contiene(lista2, tmp1->data, comp) == 1) {
            
            // Opcional: Podrías chequear si no lo agregaste ya a 'lista_resultado' para evitar repetidos
            // if (contiene(lista_resultado, tmp1->data, comp) == 0) { ... }
            
            lista_resultado = insertar_final(lista_resultado, tmp1->data, copy);
        }
    }

    return lista_resultado;
}

/* * Intersecar para SGList.
 * Aprovecha que ambas listas ya están ordenadas para avanzar
 * a la par, sin necesidad de usar bucles anidados ni "buscar".
 */
SGList sglist_intersecar(SGList lista1, SGList lista2, FuncionComparadora comp, FuncionCopia copy) {
    SGList resultado = glist_crear();
    
    GNode *tmp1 = lista1;
    GNode *tmp2 = lista2;

    // Recorremos MIENTRAS haya elementos en ambas listas
    while (tmp1 != NULL && tmp2 != NULL) {
        int comparacion = comp(tmp1->data, tmp2->data);

        if (comparacion == 0) {
            // Son iguales: encontramos una intersección. Lo agregamos.
            resultado = insertar_final(resultado, tmp1->data, copy);
            
            // Avanzamos los dos punteros para no repetir
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
            
        } else if (comparacion < 0) {
            // El elemento de lista 1 es MENOR. 
            // Como las listas están ordenadas, este elemento ya no puede 
            // estar en la lista 2. Avanzamos solo el puntero 1.
            tmp1 = tmp1->next;
            
        } else {
            // El elemento de lista 2 es MENOR. Avanzamos el puntero 2.
            tmp2 = tmp2->next;
        }
    }

    // Si una de las dos listas se termina, se corta el while, porque
    // ya es imposible que haya más elementos en común.
    
    return resultado;
}

//!SECTION

//SECTION -  EXCLUYENTES

GList glist_ordenar(GList lista, FuncionComparadora fun) {
    if (lista == NULL) return NULL;

    int hubo_cambio = 1;
    while (hubo_cambio) {
        hubo_cambio = 0;
        
        // Recorremos hasta el anteúltimo nodo
        for (GNode *tmp = lista; tmp->next != NULL; tmp = tmp->next) {
            
            // Si la función dice que el actual es MAYOR (> 0) que el siguiente...
            if (fun(tmp->data, tmp->next->data) > 0) {
                
                // Intercambiamos LOS PUNTEROS A LOS DATOS (void *), no los nodos.
                void *aux = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = aux;
                
                hubo_cambio = 1; 
            }
        }
    }
    return lista;
}

SGList sglist_fusionar(SGList lista1, SGList lista2, FuncionComparadora comp, FuncionCopia copy) {
    SGList resultado = sglist_crear();
    GNode *tmp1 = lista1;
    GNode *tmp2 = lista2;

    while (tmp1 != NULL && tmp2 != NULL) {
        if (comp(tmp1->data, tmp2->data) <= 0) {
            resultado = insertar_final(resultado, tmp1->data, copy);
            tmp1 = tmp1->next;
        } else {
            resultado = insertar_final(resultado, tmp2->data, copy);
            tmp2 = tmp2->next;
        }
    }

    // agregar lo que quede en alguna de las dos listas
    while (tmp1 != NULL) {
        resultado = insertar_final(resultado, tmp1->data, copy);
        tmp1 = tmp1->next;
    }
    while (tmp2 != NULL) {
        resultado = insertar_final(resultado, tmp2->data, copy);
        tmp2 = tmp2->next;
    }

    return resultado;
}



GList glist_concatenar(GList lista1, GList lista2) {
    // Si la primera está vacía, el resultado es directamente la segunda
    if (lista1 == NULL) return lista2;

    GNode *tmp = lista1;
    
    // Caminamos hasta el ÚLTIMO nodo de la lista 1
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    // Enganchamos la cola de la lista 1 a la cabeza de la lista 2
    tmp->next = lista2;

    return lista1;
}






//!SECTION




