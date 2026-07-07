int fibonacci(int n){

    if(n==0 || n==1) return n;

    int a=0;
    int b=1;

    for(int i=2;i<=n;i++){

        int c=a+b;
        a=b;
        b=c;
    }

    return b;
}

// Es DP porque resuelve los subproblemas una unica vez, reutilizando los ya solucionados.