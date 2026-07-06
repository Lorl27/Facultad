// Tiempo: O(n*log(n)) - Peor caso: O(n^2)
// Memoria: O(log(n))
int particionHoare(int A[], int n, int p){

    int i = 0;
    int j = n - 1;

    while(1){

        while(i < n && A[i] < p) i++;

        while(j >= 0 && A[j] > p) j--;

        if(i >= j) return i;

        int aux = A[i];
        A[i] = A[j];
        A[j] = aux;

        i++;
        j--;
    }
}


void quicksort(int A[], int n){

    if(n <= 1) return;

    int p = A[n/2];

    int pos = particionHoare(A,n,p);

    quicksort(A,pos);

    quicksort(A+pos,n-pos);
}

/*
A diferencia de Lomuto, Hoare no deja el pivote en su pos. defiitiva

HOARE
- 2 recorridos al mismo tiempo , con menos swaps
- Mayor eficiencia
- Devuelve el unto donde se cruzan los índices
- El pivote puede moverse

*/