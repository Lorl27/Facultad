// Tiempo: O(n^2)
// Memoria: O(1)
// Se nota la mejora cuando el arreglo es decreciente/aleatorio, en vez de 3 swaps solo se hace una sola copia.
// En arreglo creciente, la mejora es mínima.
void insertion_sort(int a[], int n){

    for(int i=1;i<n;i++){
        int key = a[i];
        int j = i-1;

        while(j>=0 && a[j]>key){
            a[j+1]=a[j];
            j--;
        }

        a[j+1]=key;
    }
}