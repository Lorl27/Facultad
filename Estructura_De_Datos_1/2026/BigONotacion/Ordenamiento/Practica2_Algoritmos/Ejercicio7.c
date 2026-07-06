/* La solucion que costaria O(n*log(n)) seria quicksort(a,0,n-1) y return a[n/2] */

// Necesitamos saber que elemento iria en el medio, no hace falta ordenar TODO
//Para ello: QuickSelect.

// Tiempo: O(n) , peor caso: O(n^2)
//Memoria: O(log(n)) , peor caso: O(n).
int quickselect(int a[], int inicio, int final, int k){

    if(inicio == final) return a[inicio];

    int p = particionar(a, inicio, final);

    if(p == k) return a[p];

    if(k < p) return quickselect(a, inicio, p-1, k);

    return quickselect(a, p+1, final, k);
}

int mediana(int a[], int n){

    return quickselect(a, 0, n-1, n/2);

}

