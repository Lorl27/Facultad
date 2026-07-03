// Función iterativa:
// Tiempo: O(n)
// Memoria : O(1)
// Es óptima porque si o sí hay que revisar todos los elementos.
int indiceMaximo(int array[], int n) {
    int max = 0;

    for (int x=0;x<n;x++){
        if(array[x]>array[max])max = x;
    }

    return max;
}