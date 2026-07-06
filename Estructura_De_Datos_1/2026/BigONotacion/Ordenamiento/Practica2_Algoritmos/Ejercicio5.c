// Tiempo: O(n), peor caso:  O(n^2) si es el min/maximo.
// Memoria: O(1).
int particionar(int a[], int inicio, int final){
    int pivote = a[final];
    int j = inicio; //marca la pos. donde se colocan x<= pivote

    for(int i = inicio; i < final; i++){
        if(a[i] <= pivote){
            int aux = a[i];
            a[i] = a[j];
            a[j] = aux;

            j++;
        }
    }

    int aux = a[j]; 
    a[j] = a[final];
    a[final] = aux; //colocamos el pivote en su pos. definitiva.

    return j;
}

//Llamamos con 0,n-1
//Tiempo : O(n^2) peor caso. Caso promedio: O(n*log(n))
// Memoria: O(n) peor caso. Caso promedio: O(log(n))
void quicksort(int a[], int inicio, int final){

    if(inicio >= final) return;

    int p = particionar(a, inicio, final);

    quicksort(a, inicio, p - 1);

    quicksort(a, p + 1, final);
}

//No es estable ya que 2 elementos iguales podrían cambiar su orden relativo.