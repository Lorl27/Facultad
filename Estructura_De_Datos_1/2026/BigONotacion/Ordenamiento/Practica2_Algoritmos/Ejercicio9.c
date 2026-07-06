// Si no nos importa que queden ordenados:
//Tiempo: O(n+k)
//Memria : O(k)
void primerosK(int a[], int n, int k, int res[]){

    // Coloca el elemento k-1 en su posición correcta
    quickselect(a, 0, n - 1, k - 1);

    // Copiamos los primeros k elementos
    for(int i = 0; i < k; i++){
        res[i] = a[i];
    }
}

//Si nos importa que queden ordenados:
//Tiempo: O(n+k*log(k)
//Memria : O(k)
void primerosKOrdenados(int a[], int n, int k, int res[]){

    quickselect(a, 0, n - 1, k - 1);

    for(int i = 0; i < k; i++){
        res[i] = a[i];
    }

    //Los ordenamos.
    quicksort(res, 0, k - 1);
}