// Sabemos que cada elemento debe ir en su indice correcto
// el nro 1 -> indice 0
// nro n -> indice n-1

// Cylic Sort : Intercambiamos el elemento, hasta que quede donde debe.
// Tiempo: O(n)
// Memoria: O(1)
void ordenar(int a[], int n){
    int x=0;
    while(x<n-1){
        int pos = a[x]-1;

        if(pos >= n-1 || pos == x) x++;
        else{
            int aux = a[x];
            a[x] = a[pos];
            a[pos] = aux;
        }
    }
}