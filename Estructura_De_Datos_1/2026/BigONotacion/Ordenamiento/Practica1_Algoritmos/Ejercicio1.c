//Función recursiva : 
// Tiempo : O(2^n)
// Memoria : O(n)
// Mejor claridad,muy lento cuánto mayor es n.
int fibonacci_1(int n){
    if(n==0 || n==1) return n;

    return fibonacci_1(n-1) + fibonacci_1(n-2);
}

// Función iterativa:
// Tiempo : O(n)
// Memoria : O(1)
// Es la mejor
int fibonacci_2(int n){
    if(n==0 || n==1) return n;

    int a =0;
    int b =1;

    for(int x=2; x<=n; x++){
        int aux=a+b;
        a=b;
        b=aux;
    }

    return b;
}

// Función Recursiva con memoria:
// Tiempo : O(n)
// Memoria : O(n)
// Es mejor que la recursiva común, pero menos clara.
//Se inicializa memo=-1 para todo n
int fibonacci_3(int n, int memo[]){

    if(memo[n] != -1) return memo[n]; //Evita calcular un fibonacci ya calculado

    if(n==0||n==1) return n;

    memo[n] = fibonacci_3(n-1,memo) + fibonacci_3(n-2,memo);

    return memo[n];
}