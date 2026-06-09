typedef int (*FuncionComparadora)(void *a,void *b);

void bubble_sort(void ** arreglo, int n,FuncionComparadora comp){
    for (int x=0;x<(n-1);x++){

        for (int y=0;y<(n-1-x);y++){

            if(comp(arreglo[y],arreglo[y+1])>0){
                void * tmp=arreglo[y];
                arreglo[y]=arreglo[y+1];
                arreglo[y+1] =tmp;
            }
        }
    }
}


void invertir(void **arr, int n) {
    for (int x=0;x<n/2; x++) {
        void *tmp = arr[x];
        arr[x] = arr[n-1-x];
        arr[n-1-x] = tmp;
    }
}
