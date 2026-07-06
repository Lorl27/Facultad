#define MAXN 100000

typedef struct{
    int ini;
    int fin;
} Run;

// Tiempo: Mejor caso: O(n) - Peor caso: O(n*log(n))
// Memoria: O(n)
//La idea es, aprovechar que estar parialmente ordenados y, en lugar de dividir
//el arreglo en bloques de tamaño 1 .
// Primero buscamos las subsecuentas consecutivas ya ordendas y luego, 
//aplicamos mergesort bottom-up mezclandolas de a pares, hasta obtener
// el arreglo ordenado.
void mergeSortAdaptativo(int A[], int n){

    Run runs[MAXN];

    int cantRuns = 0;

    //--------------------------------------------------
    // 1) Detectar todos los runs
    //--------------------------------------------------

    int i = 0;

    while(i < n){

        int fin = buscarRun(A,n,i);

        runs[cantRuns].ini = i;
        runs[cantRuns].fin = fin;

        cantRuns++;

        i = fin+1;
    }


    //--------------------------------------------------
    // 2) Mientras quede más de un run
    //--------------------------------------------------

    while(cantRuns > 1){

        Run nuevosRuns[MAXN];

        int nuevasCant = 0;

        int r = 0;

        while(r < cantRuns){

            // Si queda un run solo, pasa sin mezclar
            if(r == cantRuns-1){

                nuevosRuns[nuevasCant++] = runs[r];
                break;
            }

            //--------------------------------------------------
            // Mezclar dos runs consecutivos
            //--------------------------------------------------

            merge(A,runs[r].ini,runs[r].fin,runs[r+1].fin);

            nuevosRuns[nuevasCant].ini = runs[r].ini;
            nuevosRuns[nuevasCant].fin = runs[r+1].fin;

            nuevasCant++;

            r += 2;
        }

        //--------------------------------------------------
        // Actualizar lista de runs
        //--------------------------------------------------

        for(int k=0;k<nuevasCant;k++)
            runs[k]=nuevosRuns[k];

        cantRuns=nuevasCant;
    }
}


//Para encontrar una subsecuencia consecutiva:
int buscarRun(int A[],int n, int inicio){
    int x=inicio;
    while(x<n-1 && A[x]>=A[x-1]){
        x++;
    }

    return x; //Indice del ult. elemento / inica la secuncia en inicio
}
