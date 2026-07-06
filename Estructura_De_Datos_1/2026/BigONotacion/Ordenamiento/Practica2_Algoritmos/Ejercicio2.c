// Búsqueda binaria de elemento v, en un array a de longitud len ordenado
// Tiempo: O(log(n))
//Memoria : O(1)
int binsearch(int a[], int len, int v){

    int inicio = 0;
    int final = len-1;

    while(inicio <= final){ //<= para revisar el último elemento.

        int medio = inicio + (final - inicio)/2;

        if(a[medio] == v) return medio;

        if(v < a[medio]) final = medio - 1;
        else inicio = medio + 1;
    }

    return -1;
}