
// Función Recursiva:
// Tiempo : O(n)
// Memoria : O(n)
int exponencial(int b,int n){
    if(n==0) return 1;

    return b * exponencial(b,n-1);
}

// Función iterativa:
// Tiempo : O(n)
// Memoria : O(1)
// Es la mejor
int exp(int b, int n){
    int resultado=1;

    for(int x=0;x<n;x++) {
        resultado*=b;
    }

    return resultado;
}