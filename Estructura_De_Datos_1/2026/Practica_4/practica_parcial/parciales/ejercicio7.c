int es_postorder_abb_valido(void ** arr, int inicio, int fin, FuncionComparadora comp) {
    // Caso base: un árbol vacío o de 1 nodo siempre es válido
    if (inicio >= fin) return 1;

    void * raiz = arr[fin];
    
    // 1. Buscamos dónde termina el subárbol izquierdo (menores a la raíz)
    int i = inicio;
    while (i <= fin - 1 && comp(arr[i], raiz) < 0) {
        i++;
    }
    
    // 'i' ahora marca el inicio del subárbol derecho.
    int inicio_derecho = i;
    
    // 2. Verificamos que TODOS los elementos desde 'i' hasta 'fin-1' 
    // sean ESTRICTAMENTE MAYORES a la raíz.
    while (i <= fin - 1) {
        if (comp(arr[i], raiz) <= 0) {
            return 0; // ¡Hacker detectado! Hay un número menor o igual en la zona derecha
        }
        i++;
    }
    
    // 3. Si sobrevivió a la prueba, validamos recursivamente ambas mitades
    int izq_valida = es_postorder_abb_valido(arr, inicio, inicio_derecho - 1, comp);
    int der_valida = es_postorder_abb_valido(arr, inicio_derecho, fin - 1, comp);
    
    return izq_valida && der_valida;
}