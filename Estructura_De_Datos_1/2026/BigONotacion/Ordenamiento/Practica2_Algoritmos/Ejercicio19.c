/*El array esta ordenado por fecha y hora de inicio, queremos ordenarlo por fecha y hora de fin.
Como cada viaje dura <30min  , ya esta casi ordenado.

Por lo cual Insertion Sort será más rápido que QuickSort, al poder aprovechar el array semi-ordenado.
*/
#include <stdio.h>
#include <string.h>

typedef struct {
    char inicio[20];   // fecha/hora inicio
    char fin[20];      // fecha/hora fin
} Viaje;

void insertionSort(Viaje a[], int n){
    for(int i = 1; i < n; i++){
        Viaje key = a[i];
        int j = i - 1;

        // mover elementos mayores que key.fin
        while(j >= 0 && strcmp(a[j].fin, key.fin) > 0){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}


int comparar(const void *x, const void *y){
    const Viaje *v1 = x;
    const Viaje *v2 = y;
    return strcmp(v1->fin, v2->fin);
}

void quickSort(Viaje a[], int n){
    qsort(a, n, sizeof(Viaje), comparar);
}



int main(){
    Viaje viajes[] = {
        {"2026-07-06 08:00", "2026-07-06 08:20"},
        {"2026-07-06 08:05", "2026-07-06 08:25"},
        {"2026-07-06 08:10", "2026-07-06 08:15"},
        {"2026-07-06 08:12", "2026-07-06 08:28"}
    };
    int n = sizeof(viajes)/sizeof(viajes[0]);

    // Probar Insertion Sort
    insertionSort(viajes, n);

    // Probar QuickSort
    // quickSort(viajes, n);

    for(int i=0; i<n; i++){
        printf("Inicio: %s | Fin: %s\n", viajes[i].inicio, viajes[i].fin);
    }
    return 0;
}
