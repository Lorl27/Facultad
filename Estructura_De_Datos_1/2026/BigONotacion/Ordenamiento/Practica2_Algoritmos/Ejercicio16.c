// Tiempo: O(log(n) .; ⌈log^2(𝑛)⌉+1 en el peor caso.
// Memoria: O(1)
int busqueda_binaria_opt(int a[], int n, int v){
    int izq = -1;
    int der = n;

    while(izq + 1 < der){
        int mid = (izq + der) / 2;

        if(a[mid] <= v) izq = mid; //buscamos el ultimo indice i / a[i]<=v
        else der = mid;
    }

    // Al salir, izq es el último índice con a[izq] <= v
    if(izq >= 0 && a[izq] == v) return izq;  // encontrado

    return -1;// no está
}
