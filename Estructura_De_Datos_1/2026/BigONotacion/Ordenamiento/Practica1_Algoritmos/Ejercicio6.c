/* A:


Caso 1: El primer elemento ya es un pico : A[0]>= A[1].

Caso 2: No es un pico, seguimos buscando mientras crece el array: A[i]<A[i+1]

- Si en un momento deja de crecer: Encontramos el pico.
- Si nunca deja de crecer, el pico termina siendo el último elemento.

Por lo tanto, siempre existe al menos un pico.
*/

//B:

// Tiempo: O(n) (Peor caso)
// Memoria: O(1)
int buscarPico(int A[], int n){

    if(n == 1) return 0;

    if(A[0] >= A[1]) return 0; //El primero es

    for(int x=1;x<n-1;x++){
        if(A[x] >= A[x-1] && A[x] >= A[x+1])
            return x;
    }

    return n - 1; //Si ninguno lo es: el ùltimo es entonces.
}

//C: Sí, Se puede hacer en O(log(n))

// Tiempo: O(log(n))
// Memoria: O(log(n))
int buscarPico_v2(int A[], int lo, int hi) {

    if (lo == hi) return lo;

    int medio = (lo + hi) / 2;

    if (A[medio] < A[medio + 1])
        return buscarPico_v2(A, medio + 1, hi);

    return buscarPico_v2(A, lo, medio);
}

/*D: Sí.
En A. No siempre existe un pico.
El B. habría que cambiar y retornar -1 si no encuentra el pico.
El C. serviría.

*/


