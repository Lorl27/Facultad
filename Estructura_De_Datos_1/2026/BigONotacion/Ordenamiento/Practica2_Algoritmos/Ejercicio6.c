//Evita ordenar los repetidos.
void particionar3(int a[], int inicio, int final, int *lt, int *gt){
    int pivote = a[inicio];
    *lt = inicio;
    *gt = final;

    int i = inicio;

    while(i <= *gt){
        if(a[i] < pivote){
            swap(a[i], a[*lt]);

            i++;
            (*lt)++;
        }
        else if(a[i] > pivote){

            swap(a[i], a[*gt]);

            (*gt)--;
        }
        else i++;
    }
}

//Tiempo : O(n) peor caso. Caso promedio: O(n*log(n))
// Memoria:  O(log(n))
void quicksort3(int a[], int inicio, int final){

    if(inicio >= final) return;

    int lt, gt;

    particionar3(a, inicio, final, &lt, &gt);

    quicksort3(a, inicio, lt-1);

    quicksort3(a, gt+1, final);
}