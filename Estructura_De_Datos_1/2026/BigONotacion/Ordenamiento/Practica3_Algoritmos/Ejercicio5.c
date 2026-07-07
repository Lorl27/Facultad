/*

El arreglo, tras partilo a mitad, queda dividido en 3 lugares:
Izq - medio - der

¿Còmo calculamos el que cruza? cruza = mejor suma izq + mejor suma der
*/


#include <stdio.h>
#include <limits.h>

int max(int a,int b){
    return (a>b)?a:b;
}

int max3(int a,int b,int c){
    return max(max(a,b),c);
}

int maxCruza(int A[],int l,int m,int r){

    int suma=0;
    int mejorIzq=INT_MIN;

    for(int i=m;i>=l;i--){
        suma+=A[i];
        if(suma>mejorIzq) mejorIzq=suma;
    }

    suma=0;
    int mejorDer=INT_MIN;

    for(int i=m+1;i<=r;i++){
        suma+=A[i];
        if(suma>mejorDer) mejorDer=suma;
    }

    return mejorIzq+mejorDer;
}

// Tiempo : O(n*log(n))
//Memoria : O(log(n))
int MaxSubarreglo(int A[],int l,int r){
    if(l==r) return A[l];

    int m=(l+r)/2;

    int izq=maxSubarreglo(A,l,m);

    int der=maxSubarreglo(A,m+1,r);

    int cruz=maxCruza(A,l,m,r);

    return max3(izq,der,cruz);
}
