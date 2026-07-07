/*
A: version clasica :
TIempo: O(n)
Memoria : O(1)

Realiza 2(n-1) comparaciones
*/

typedef struct {
    int min;
    int max;
} MinMax;

MinMax ver_classic(int A[],int n){
    MinMax resultado;
    resultado.min = A[0];
    resultado.max = A[0];

    for(int i = 1; i < n; i++) {
        if(A[i] < resultado.min) resultado.min = A[i];
        if(A[i] > resultado.max) resultado.max = A[i];
    }

    return resultado;
}

// B: Realiza  3n/2 -2 comparaciones
// Tiempo: O(n)
MinMax extremos(int A[], int l, int r){

    MinMax res;

    if(l==r){
        res.min=A[l];
        res.max=A[l];
        return res;
    }

    if(r==l+1){
        if(A[l]<A[r]){
            res.min=A[l];
            res.max=A[r];
        }else{
            res.min=A[r];
            res.max=A[l];
        }

        return res;
    }


    int m=(l+r)/2;

    MinMax izq=extremos(A,l,m);

    MinMax der=extremos(A,m+1,r);

    if(izq.min<der.min) res.min=izq.min;
    else res.min=der.min;


    if(izq.max>der.max)res.max=izq.max;
    else res.max=der.max;

    return res;
}
