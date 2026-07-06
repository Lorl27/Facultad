// Vista en ejericio7 (quickselect).

// Tiempo: O(n) , peor caso: O(n^2)
//Memoria: O(log(n)) , peor caso: O(n).
int quickselect(int a[], int inicio, int final, int k){

    if(inicio == final) return a[inicio];

    int p = particionar(a, inicio, final);

    if(p == k) return a[p];

    if(k < p) return quickselect(a, inicio, p-1, k);

    return quickselect(a, p+1, final, k);
}