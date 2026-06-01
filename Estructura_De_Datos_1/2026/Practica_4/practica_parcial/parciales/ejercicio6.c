// --- Función auxiliar: Hundir para MIN-HEAP ---
void hundir_min(void ** arr, int pos, int n, FuncionComparadora comp) {
    int es_menor = 1;
    while(2 * pos <= n && es_menor) {
        int k = 2 * pos; // Hijo izquierdo
        
        // Si hay hijo derecho y es MENOR que el izquierdo (usando comp)
        // comp(izq, der) > 0 significa que izquierdo es mayor, así que nos quedamos con el derecho.
        if (k + 1 <= n && comp(arr[k], arr[k+1]) > 0) {
            k = k + 1; // k apunta al hijo más CHICO
        }

        // Si mi padre (pos) es MAYOR que mi hijo más chico (k), me hundo.
        if (comp(arr[pos], arr[k]) > 0) {
            void * temp = arr[pos];
            arr[pos] = arr[k];
            arr[k] = temp;
            pos = k; // Sigo bajando
        } else {
            es_menor = 0; // Ya estoy bien ubicado
        }
    }
}

// --- FUNCIÓN PRINCIPAL ---
void max_heap_to_min_heap(void ** arr, int n, FuncionComparadora comp) {
    if (arr == NULL || n <= 1) return;

    // Aplicamos Floyd (Heapify): Empezamos desde el último padre y hundimos
    // OJO: El índice 0 no se usa, así que los elementos válidos son de 1 a n.
    for (int i = n / 2; i >= 1; i--) {
        hundir_min(arr, i, n, comp);
    }
}