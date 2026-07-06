//Devuelve el indice donde deberia insertarse x.
int buscarPosicion(int A[], int inicio, int final, int x){

    while(inicio <= final){

        int mid = (inicio + final) / 2;

        if(A[mid] <= x) inicio = mid + 1;
        else final = mid - 1;
    }

    return inicio;
}


#include <string.h> // memmove
/*
Tiempo : O(n^2) peor caso ; mejor  caso: O(n*log(n))
Memoria: O(1)
-------------
memmove es equivalente a : 
for(int j=i; j>pos; j--)
    A[j]=A[j-1];

---------
*/
void insertionSortBinario(int A[], int n){
    for(int i = 1; i < n; i++){
        int key = A[i];

        // Buscar la posición correcta dentro del prefijo A[0..i-1]
        int pos = buscarPosicion(A, 0, i - 1, key);

        // Desplazar los elementos una posición a la derecha
        memmove(&A[pos + 1], &A[pos], (i - pos) * sizeof(int));

        // Insertar el elemento
        A[pos] = key;
    }
}