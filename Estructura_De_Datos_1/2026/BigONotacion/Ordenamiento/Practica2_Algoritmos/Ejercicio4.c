// Tiempo: O(n)
// Memoria: O(n)
void merge(int a[], int aux[], int izq, int medio, int der){

    int i = izq;  //recorre mitad izq
    int j = medio + 1;  //recorre mitad derecha
    int k = izq;  //escribe en el array aux.

    while(i <= medio && j <= der){ //Mientras en las 2 mitades haya elementos..
        if(a[i] <= a[j]) aux[k++] = a[i++]; //Copiamos el menor en aux[k]
        else aux[k++] = a[j++];
    }

    while(i <= medio){ //Si quedan elementos en la mitad izq, lo copiamos a aux
        aux[k++] = a[i++];
    }

    while(j <= der){ //Lo mismo para la mitad derecha
        aux[k++] = a[j++];
    }

    for(i = izq; i <= der; i++){ //Luego, pasamos los elementos de aux-->a
        a[i] = aux[i];
    }
}

//Llamarlo en 0, n-1 - En aux se guardara el array resultante.
// Tiempo : O(n* log(n))
// Memoria: O(n)
void mergesort(int a[], int aux[], int izq, int der){

    if(izq >= der) return;

    int medio = (izq + der) / 2;

    mergesort(a, aux, izq, medio);

    mergesort(a, aux, medio + 1, der);

    merge(a, aux, izq, medio, der);
}


//Es estable ya que cuando los elementos son iguales, elegimos primero al de la izquierdas.