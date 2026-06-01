void ordenar(int* arr, int n) {
    if (arr == NULL || n <= 1) return;

    // 1. CONSTRUIR EL MAX-HEAP (Heapify)
    // Empezamos desde el último padre del árbol hacia la raíz (índice 0).
    // El profesor te regaló la función "padre" para calcularlo exactamente.
    for (int i = padre(n - 1); i >= 0; i--) {
        hundir(i, arr, n);
    }

    // 2. ORDENAMIENTO (HeapSort)
    // i representa el tamaño "vivo" del Heap que va achicándose.
    for (int i = n - 1; i > 0; i--) {
        // Ponemos el elemento más grande (arr[0]) al final del arreglo (arr[i])
        swap_int(&arr[0], &arr[i]);

        // Hundimos el elemento que quedó en la raíz, pero le decimos a la función
        // que el tamaño del Heap ahora es 'i' (ignorando los que ya ordenamos al final)
        hundir(0, arr, i);
    }
}