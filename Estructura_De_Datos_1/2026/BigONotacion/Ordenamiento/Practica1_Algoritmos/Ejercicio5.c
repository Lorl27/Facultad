
// Tiempo : O(n)
// Memoria : O(1)
// J(1)=0 , J(n)=(J(n-1)+2) mod n
int sobreviviente(int n){

    int res = 0;

    for(int i = 2; i <= n; i++){
        res = (res + 2) % i;
    }

    return res + 1;
}

// Otra forma es con la fórmula: J(N)= 2L+1, con L=2^m - N, con m: mayor potencia de 2 <=N
// Termina siendo de Tiempo O(1) si se conoce la potencia de 2, ò en el peor caso: O(log(n)). 