// Función Recursiva:
// Tiempo : O(log(n))
// Memoria : O(log(n)
// Si n par: b^n = (b^2)^(n/2)
// si n impar:  b^n = b*b^(n-1)
int exp(int b, int n){
    if(n==0) return 1;

    if(n%2==0) return exp(b*b,n/2);

    return b*exp(b,n-1);
}

// Función Recursiva:
// Tiempo : O(log(n))
// Memoria : O(log(n)
// Si n par: b^n = (n/2)*(n/2)
// si n impar:  b^n = b*(n/2)*(n/2)
int exp_mejorada(int b, int n){
    if(n==0) return 1;

    int mitad = exp_mejorada(b,n/2);

    if(n%2==0) return mitad*mitad;

    return b*mitad*mitad;
}