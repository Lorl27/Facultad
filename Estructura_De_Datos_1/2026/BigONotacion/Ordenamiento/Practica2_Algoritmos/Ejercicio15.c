#define M 20

void quicksort(int a[], int inicio, int fin){

    if(fin-inicio+1 <= M) return;

    int p = particionar(a,inicio,fin);

    quicksort(a,inicio,p-1);

    quicksort(a,p+1,fin);
}


// En llamada:
//quicksort(a,0,n-1);

//insertionSort(a,n);


// Costo total: O(n*log(n))
// Mejora muchisimo ya que divido hasta que este casi todo ordenado,
// entonces se lo paso a insertionSort que funciona baŕbaro para pequeños semi-ordenados 
