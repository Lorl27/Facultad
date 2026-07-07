// Ordenamos por hora de finalizacion y Elegimos la actividad que termina antes.

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int inicio;
    int fin;
}Actividad;

int comparar(const void *a,const void *b){

    Actividad *x=(Actividad*)a;
    Actividad *y=(Actividad*)b;

    return x->fin-y->fin;
}

/* Tiempo: O(n*log(n) peor  caso. Si estan ordenadas. O(n)
Memoria: O(n)
*/
void seleccionar(Actividad A[],int n){

    qsort(A,n,sizeof(Actividad),comparar);

    printf("Actividades elegidas:\n");

    printf("(%d,%d)\n",A[0].inicio,A[0].fin);

    int ultimoFin=A[0].fin;

    for(int i=1;i<n;i++){
        if(A[i].inicio>=ultimoFin){
            printf("(%d,%d)\n",A[i].inicio,A[i].fin);
            ultimoFin=A[i].fin;
        }
    }
}


int main(){

    Actividad A[]={
        {1,4},
        {3,5},
        {0,6},
        {5,7},
        {8,9}
    };

    seleccionar(A,5);

    return 0;
}