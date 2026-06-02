// ==========================================================
// MÓDULOS AUXILIARES (Tus herramientas principales)
// ==========================================================

// 1. Extraer a arreglo (In-Order: Menor a Mayor)
void volcar_arbol_a_arreglo(AVL arbol, void **arr, int *indice) {
    if (arbol == NULL) return;
    
    volcar_arbol_a_arreglo(arbol->izq, arr, indice);
    arr[*indice] = arbol->dato;
    (*indice)++;                
    volcar_arbol_a_arreglo(arbol->der, arr, indice);
}

// 2. Arreglo ordenado a AVL (Divide y Vencerás Bottom-Up)
AVL arr_ordenado_to_avl(void ** arr, int n){
    if(arr == NULL || n <= 0) return NULL;
    int indice = 0; // Para arreglos, arrancamos en 0
    return ordenado_avl_aux(arr, &indice, n);
}

AVL ordenado_avl_aux(void ** ar, int * indice, int n){
    if(n <= 0) return NULL;

    AVL izq = ordenado_avl_aux(ar, indice, n/2);

    AVL arbol = malloc(sizeof(struct _AVL_Nodo)); // CORREGIDO
    arbol->dato = ar[*indice];
    (*indice)++;

    AVL der = ordenado_avl_aux(ar, indice, n - (n/2) - 1);

    arbol->izq = izq;
    arbol->der = der;
    arbol->altura = 1 + max_altura_hijos(arbol);

    return arbol;
}

// 3. Convertir arreglo a Heap (Floyd)
void aplicar_heapify(BHeap heap, FuncionComparadora comp) {
    for (int i = heap->ultimo / 2; i >= 1; i--) {
        bheap_hundir(heap, i, comp);
    }
}


// Función auxiliar (El "Sift-Up" o "Trepar")
void bheap_subir(BHeap heap, int pos, FuncionComparadora comp) {
    // Mientras no seamos la raíz y seamos MAYORES que nuestro padre, trepamos
    while (pos > 1 && comp(heap->arr[pos], heap->arr[pos/2]) > 0) {
        void * temp = heap->arr[pos];
        heap->arr[pos] = heap->arr[pos/2];
        heap->arr[pos/2] = temp;
        
        pos = pos / 2; // Actualizamos la posición para seguir subiendo
    }
}


BHeap bheap_insertar(BHeap heap, void * elemento, FuncionCopiadora copy, FuncionComparadora comp){
    if(heap==NULL) return heap;

    // ¿El arreglo está lleno? 
    if(heap->ultimo == heap->capacidad - 1){
        heap->capacidad *= 2; // Duplicamos capacidad
        heap->arr = realloc(heap->arr, sizeof(void *) * heap->capacidad);
    }

    heap->ultimo++;
    heap->arr[heap->ultimo]=copy(elemento);

   bheap_subir(heap, heap->ultimo, comp);

    return heap;
}

// Función auxiliar (El "Sift-Down" o "Hundimiento")
void bheap_hundir(BHeap heap, int pos, FuncionComparadora comp) {
    int es_mayor = 1;
    while(2 * pos <= heap->ultimo && es_mayor) {
        int k = 2 * pos; // Hijo izquierdo
        
        // Si hay derecho y es mayor que el izquierdo, apuntamos al derecho
        if(k + 1 <= heap->ultimo && comp(heap->arr[k+1], heap->arr[k]) > 0) {
            k = k + 1;
        }

        // Si soy menor que mi hijo mayor, me hundo
        if(comp(heap->arr[pos], heap->arr[k]) < 0) {
            void * temp = heap->arr[pos];
            heap->arr[pos] = heap->arr[k];
            heap->arr[k] = temp;
            pos = k; // Sigo bajando
        } else {
            es_mayor = 0; // Si soy mayor, ya estoy bien ubicado
        }
    }
}

BHeap bheap_eliminar_maximo(BHeap heap, FuncionComparadora comp, FuncionDestructora destroy){
    if(bheap_es_vacio(heap)) return heap;

    // 1. Destruimos el máximo (la raíz)
    destroy(heap->arr[1]);

    // 2. Agarramos al último y lo ponemos en la raíz. Achicamos el Heap.
    heap->arr[1] = heap->arr[heap->ultimo];
    heap->ultimo--;

    bheap_hundir(heap, 1, comp);

    return heap;
}

// ==========================================================
// RESOLUCIONES DE EXAMEN (Combinando las herramientas)
// ==========================================================

// SECTION - AVL TO HEAP
BHeap avl_to_heap(AVL arbol, FuncionComparadora comp){
    int n = contar_nodos_abb(arbol); // Asumimos que la tienes

    BHeap heap = malloc(sizeof(struct _BHeap)); // CORREGIDO
    heap->capacidad = n + 1;                    // CORREGIDO
    heap->ultimo = n;
    heap->arr = malloc(sizeof(void*) * heap->capacidad);

    if(n == 0) return heap;

    int indice = 1; // CORREGIDO: ¡Los Heaps empiezan en 1!
    volcar_arbol_a_arreglo(arbol, heap->arr, &indice);

    aplicar_heapify(heap, comp);

    return heap;
}

//SECTION -  AB TO ABB OR AVL
AVL ab_general_to_abb(BSTree arbol, FuncionComparadora comp) {
    int n = bstree_nnodos(arbol);
    if (n == 0) return NULL;

    void ** arr = malloc(sizeof(void *) * n);
    
    int indice = 0;
    // 1. Volcamos los datos. AB DESORDENADOS AVL ORDENADOS NO HACE FALTA ORDENAS CON HEAP.
    volcar_arbol_a_arreglo((AVL)arbol, arr, &indice); 
    
    // 2. ¡PASO CLAVE! Lo ordenamos en el arreglo usando nuestro módulo de Heap O(n log n)
    ordenar_arreglo_con_heap(arr, n, comp);
    
    // 3. Ahora que está ordenado, armamos el árbol perfecto en O(n)
    AVL nuevo_arbol = arr_ordenado_to_avl(arr, n);
    
    free(arr);
    return nuevo_arbol;
}

//!SECTION

// SECTION - HEAP A AVL
AVL heap_to_avl(BHeap heap, FuncionComparadora comp) {
    if (heap == NULL || heap->ultimo == 0) return NULL;
    
    int n = heap->ultimo;

    BHeap heap_temp = malloc(sizeof(struct _BHeap));
    heap_temp->capacidad = heap->capacidad;
    heap_temp->ultimo = heap->ultimo;
    heap_temp->arr = malloc(sizeof(void*) * heap->capacidad);
    
    for(int i = 1; i <= n; i++) {
        heap_temp->arr[i] = heap->arr[i]; 
    }

    void ** arr_ordenado = malloc(sizeof(void*) * n);
    
    for (int i = n - 1; i >= 0; i--) {
        arr_ordenado[i] = heap_temp->arr[1]; 
        heap_temp = bheap_eliminar_maximo(heap_temp, comp, no_destruir_dato);
    }

    free(heap_temp->arr);
    free(heap_temp);

    AVL nuevo_avl = arr_ordenado_to_avl(arr_ordenado, n); // CORREGIDO

    free(arr_ordenado);
    return nuevo_avl;
}

// SECTION - ORDENAR ARREGLO DESORDENADO A AVL
void ordenar_arreglo_con_heap(void ** arr, int n, FuncionComparadora comp) {
    if (arr == NULL || n <= 1) return;

    BHeap heap = bheap_crear_desde_arr(arr, n, no_copiar, comp);

    for (int i = n - 1; i >= 0; i--) {
        arr[i] = heap->arr[1]; 
        heap = bheap_eliminar_maximo(heap, comp, no_destruir_nada);
    }

    bheap_destruir(heap, no_destruir_nada);
}

AVL unsorted_arr_to_avl(void ** arr, int n, FuncionComparadora comp) {
    ordenar_arreglo_con_heap(arr, n, comp);
    return arr_ordenado_to_avl(arr, n); // CORREGIDO
}

BHeap bheap_crear_desde_arr(void **arr, int largo, FuncionCopiadora copiar,FuncionComparadora comp){
    // Pedimos capacidad + 1 porque en los Heaps ignoramos el índice 0
    BHeap heap = bheap_crear(largo + 1); 
    
    if(largo == 0 || arr == NULL) return heap;

    // 1. Copiamos los datos "a lo bruto" (queda un árbol desordenado)
    for(int i = 0; i < largo; i++) {
        heap->arr[i + 1] = copiar(arr[i]);
    }
    heap->ultimo = largo;

    aplicar_heapify(heap, comp);

    return heap;
}