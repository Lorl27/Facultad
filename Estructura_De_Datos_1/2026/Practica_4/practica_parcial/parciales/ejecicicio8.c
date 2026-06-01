// --- Función auxiliar 1: Volcar punteros del AVL al arreglo ---
void volcar_avl_a_arreglo(AVL arbol, void **arr, int *indice) {
    if (arbol == NULL) return;
    
    // Un recorrido In-Order simple para visitar todos los nodos
    volcar_avl_a_arreglo(arbol->izq, arr, indice);
    
    arr[*indice] = arbol->dato;
    (*indice)++;
    
    volcar_avl_a_arreglo(arbol->der, arr, indice);
}

// --- FUNCIÓN PRINCIPAL ---
BHeap avl_a_heap_de_promedios(AVL arbol_legajos, int cant_alumnos, FuncionComparadora comp_promedios) {
    // 1. Creamos el Heap vacío con la capacidad exacta
    // Ojo: Si usaste bheap_crear, internamente debería hacer el malloc del cascarón.
    // Usamos cant_alumnos + 1 porque el índice 0 se ignora en los Heaps matemáticos.
    BHeap heap_promedios = bheap_crear(cant_alumnos + 1);
    
    if (cant_alumnos == 0 || arbol_legajos == NULL) {
        return heap_promedios;
    }

    // 2. Volcamos los punteros físicos del AVL al arreglo del Heap (O(n))
    int indice = 1; // ¡Empezamos en 1!
    volcar_avl_a_arreglo(arbol_legajos, heap_promedios->arr, &indice);
    heap_promedios->ultimo = cant_alumnos;

    // 3. HEAPIFY en O(n): Aplicamos la función auxiliar hundir desde la mitad hacia arriba
    // Esto ordena el arreglo en base a la nueva regla (comp_promedios)
    for (int i = heap_promedios->ultimo / 2; i >= 1; i--) {
        // Asumimos que tienes "bheap_hundir" a tu disposición según el enunciado
        bheap_hundir(heap_promedios, i, comp_promedios);
    }

    // ¡Listo! Devolvemos la nueva estructura que apunta a los mismos alumnos físicos.
    return heap_promedios;
}